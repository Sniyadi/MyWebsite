"""
PAC1711 4-20mA Receiver GUI
Real-time current monitoring with manual pressure logging
Dual Y-axis graph: Current (auto) + Pressure (manual entry)
"""

import sys
import time
import re
import os
from collections import deque
from threading import Thread, Event

import numpy as np
import serial
import serial.tools.list_ports
from PySide6.QtCore import Qt, QTimer, Signal, QObject
from PySide6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
    QLabel, QComboBox, QPushButton, QLineEdit, QFrame, QGroupBox,
    QStatusBar, QTabWidget, QTextEdit, QScrollArea
)
from PySide6.QtGui import QFont, QPixmap
import pyqtgraph as pg


# Constants
GRAPH_WINDOW = 30  # seconds
UPDATE_RATE_MS = 100  # GUI update rate in milliseconds


class SerialSignals(QObject):
    """Signals for thread-safe communication from serial thread to GUI"""
    data_received = Signal(float)  # current in mA
    error = Signal(str)
    connected = Signal()
    disconnected = Signal()


class SerialReader(Thread):
    """Background thread for reading serial data"""

    def __init__(self, signals):
        super().__init__(daemon=True)
        self.signals = signals
        self.serial_port = None
        self.stop_event = Event()
        self.port_name = None
        self.baud_rate = 115200

    def connect(self, port_name, baud_rate=115200):
        self.port_name = port_name
        self.baud_rate = baud_rate
        self.stop_event.clear()

    def disconnect(self):
        self.stop_event.set()

    def run(self):
        try:
            self.serial_port = serial.Serial(
                self.port_name,
                self.baud_rate,
                timeout=1
            )
            self.signals.connected.emit()

            buffer = ""
            # Patterns to match current values:
            # 1. "I:xx.xx" format (simple)
            # 2. "PAC1711_GetISENSE_mA(): xx.xx" format (existing PIC18 output)
            pattern_simple = re.compile(r'I:(\d+\.?\d*)')
            pattern_pic18 = re.compile(r'PAC1711_GetISENSE_mA\(\):\s*(\d+\.?\d*)')

            while not self.stop_event.is_set():
                if self.serial_port.in_waiting > 0:
                    try:
                        data = self.serial_port.read(self.serial_port.in_waiting).decode('utf-8', errors='ignore')
                        buffer += data

                        # Process complete lines
                        while '\n' in buffer:
                            line, buffer = buffer.split('\n', 1)
                            line = line.strip()

                            # Try to parse current value (check both patterns)
                            match = pattern_simple.search(line)
                            if not match:
                                match = pattern_pic18.search(line)
                            if match:
                                current_mA = float(match.group(1))
                                self.signals.data_received.emit(current_mA)

                    except Exception as e:
                        pass  # Ignore decode errors

                time.sleep(0.01)  # Small delay to prevent CPU spinning

        except serial.SerialException as e:
            self.signals.error.emit(f"Serial error: {str(e)}")
        finally:
            if self.serial_port and self.serial_port.is_open:
                self.serial_port.close()
            self.signals.disconnected.emit()


class LargeValueDisplay(QFrame):
    """Large numeric display widget for output values"""

    def __init__(self, title, unit, color="#00ff00", parent=None):
        super().__init__(parent)
        self.setFrameStyle(QFrame.Box | QFrame.Raised)
        self.setLineWidth(2)
        self.setStyleSheet("background-color: #1e1e1e; border-radius: 10px;")

        layout = QVBoxLayout(self)

        # Title label
        self.title_label = QLabel(title)
        self.title_label.setAlignment(Qt.AlignCenter)
        self.title_label.setStyleSheet("color: #888888; font-size: 14px; font-weight: bold;")
        layout.addWidget(self.title_label)

        # Value label
        self.value_label = QLabel("--.-")
        self.value_label.setAlignment(Qt.AlignCenter)
        font = QFont("Consolas", 48, QFont.Bold)
        self.value_label.setFont(font)
        self.value_label.setStyleSheet(f"color: {color};")
        layout.addWidget(self.value_label)

        # Unit label
        self.unit_label = QLabel(unit)
        self.unit_label.setAlignment(Qt.AlignCenter)
        self.unit_label.setStyleSheet("color: #888888; font-size: 16px;")
        layout.addWidget(self.unit_label)

    def set_value(self, value):
        if value is None:
            self.value_label.setText("--.-")
        else:
            self.value_label.setText(f"{value:.2f}")


class PressureInputWidget(QFrame):
    """Widget for manual pressure input (Pmin or Pmax) with Log button"""

    pressure_logged = Signal(float)

    def __init__(self, title, color, parent=None):
        super().__init__(parent)
        self.color = color
        self.setFrameStyle(QFrame.Box | QFrame.Raised)
        self.setLineWidth(2)
        self.setStyleSheet("background-color: #1e1e1e; border-radius: 10px;")

        layout = QVBoxLayout(self)

        # Title label
        title_label = QLabel(title)
        title_label.setAlignment(Qt.AlignCenter)
        title_label.setStyleSheet("color: #888888; font-size: 14px; font-weight: bold;")
        layout.addWidget(title_label)

        # Input field
        self.pressure_input = QLineEdit()
        self.pressure_input.setAlignment(Qt.AlignCenter)
        font = QFont("Consolas", 32, QFont.Bold)
        self.pressure_input.setFont(font)
        self.pressure_input.setStyleSheet(
            f"color: {color}; background-color: #2a2a2a; border: 2px solid {color}; border-radius: 5px;"
        )
        self.pressure_input.setPlaceholderText("0.00")
        self.pressure_input.returnPressed.connect(self.log_pressure)
        layout.addWidget(self.pressure_input)

        # Unit label
        unit_label = QLabel("PSI")
        unit_label.setAlignment(Qt.AlignCenter)
        unit_label.setStyleSheet("color: #888888; font-size: 14px;")
        layout.addWidget(unit_label)

        # Log button
        self.log_btn = QPushButton("Log")
        self.log_btn.setStyleSheet(
            f"font-weight: bold; font-size: 12px; padding: 6px; "
            f"background-color: {color}; color: black; border-radius: 5px;"
        )
        self.log_btn.clicked.connect(self.log_pressure)
        layout.addWidget(self.log_btn)

        # Last logged value
        self.last_logged_label = QLabel("Last: --.-")
        self.last_logged_label.setAlignment(Qt.AlignCenter)
        self.last_logged_label.setStyleSheet("color: #666666; font-size: 11px;")
        layout.addWidget(self.last_logged_label)

    def log_pressure(self):
        try:
            value = float(self.pressure_input.text())
            self.pressure_logged.emit(value)
        except ValueError:
            pass  # Ignore invalid input

    def set_logged_value(self, value):
        """Update the last logged label"""
        self.last_logged_label.setText(f"Last: {value:.2f}")

    def show_error(self, message):
        """Show error in last logged label"""
        self.last_logged_label.setText(message)
        self.last_logged_label.setStyleSheet("color: #ff4444; font-size: 11px;")


def calculate_pressure(current_mA, pmin, pmax):
    """
    Convert 4-20mA current to pressure using linear formula

    Formula: P = m * I + b
    where: m = (Pmax - Pmin) / (20 - 4) = (Pmax - Pmin) / 16
           b = Pmin - m * 4

    This reverses the transmitter's pressure-to-current conversion.

    Args:
        current_mA: Measured current in milliamps (4-20mA range)
        pmin: Minimum pressure at 4mA (user input)
        pmax: Maximum pressure at 20mA (user input)

    Returns:
        Calculated pressure in PSI, or None if inputs are invalid

    Example:
        pressure = calculate_pressure(12.0, 0.0, 50.0)  # Returns 25.0 PSI
    """
    if pmin is None or pmax is None:
        return None

    if pmin >= pmax:
        return None  # Invalid range

    m = (pmax - pmin) / 16.0  # slope: 4-20mA = 16mA span
    b = pmin - (m * 4.0)      # intercept: pressure at 4mA
    pressure = (m * current_mA) + b

    return pressure


class PAC1711GUI(QMainWindow):
    """Main application window"""

    def __init__(self):
        super().__init__()
        self.setWindowTitle("PAC1711 4-20mA Receiver")
        self.setMinimumSize(900, 700)

        # Data storage
        self.current_buffer = deque(maxlen=int(GRAPH_WINDOW * 20))  # ~20 samples/sec max
        self.pmin_buffer = []  # Manual Pmin entries - keep all history
        self.pmax_buffer = []  # Manual Pmax entries - keep all history
        self.pressure_calc_buffer = deque(maxlen=int(GRAPH_WINDOW * 20))  # Calculated pressure - auto
        self.sample_count = 0
        self.last_current = None
        self.last_pmin = None
        self.last_pmax = None
        self.last_pressure_calc = None
        self.start_time = time.time()  # Reference time for positive X-axis

        # Serial reader
        self.serial_signals = SerialSignals()
        self.serial_reader = None
        self.is_connected = False

        # Connect signals
        self.serial_signals.data_received.connect(self.on_data_received)
        self.serial_signals.error.connect(self.on_serial_error)
        self.serial_signals.connected.connect(self.on_connected)
        self.serial_signals.disconnected.connect(self.on_disconnected)

        self.setup_ui()
        self.setup_graph()

        # Update timer for graph
        self.update_timer = QTimer()
        self.update_timer.timeout.connect(self.update_graph)
        self.update_timer.start(UPDATE_RATE_MS)

        # Refresh COM ports on startup
        self.refresh_ports()

    def setup_ui(self):
        """Create the user interface"""
        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        main_layout = QVBoxLayout(central_widget)
        main_layout.setSpacing(10)

        # === Connection Section ===
        conn_group = QGroupBox("Connection")
        conn_layout = QHBoxLayout(conn_group)

        conn_layout.addWidget(QLabel("COM Port:"))
        self.port_combo = QComboBox()
        self.port_combo.setMinimumWidth(150)
        conn_layout.addWidget(self.port_combo)

        self.refresh_btn = QPushButton("Refresh")
        self.refresh_btn.clicked.connect(self.refresh_ports)
        conn_layout.addWidget(self.refresh_btn)

        conn_layout.addWidget(QLabel("Baud:"))
        self.baud_combo = QComboBox()
        self.baud_combo.addItems(["9600", "19200", "38400", "57600", "115200"])
        self.baud_combo.setCurrentText("115200")
        conn_layout.addWidget(self.baud_combo)

        self.connect_btn = QPushButton("Connect")
        self.connect_btn.clicked.connect(self.toggle_connection)
        self.connect_btn.setStyleSheet("font-weight: bold;")
        conn_layout.addWidget(self.connect_btn)

        conn_layout.addStretch()
        main_layout.addWidget(conn_group)

        # === Value Displays ===
        display_layout = QHBoxLayout()

        # Current output (auto from PAC1711) - Blue
        self.current_display = LargeValueDisplay("CURRENT OUTPUT", "mA", color="#0066FF")
        display_layout.addWidget(self.current_display)

        # Calculated pressure (auto from formula) - Red
        self.pressure_calc_display = LargeValueDisplay("PRESSURE (Calc)", "PSI", color="#FF0000")
        display_layout.addWidget(self.pressure_calc_display)

        # Pmin input (manual entry) - Yellow
        self.pmin_input_widget = PressureInputWidget("Pmin INPUT", "#CCAA00")
        self.pmin_input_widget.pressure_logged.connect(self.on_pmin_logged)
        display_layout.addWidget(self.pmin_input_widget)

        # Pmax input (manual entry) - Green
        self.pmax_input_widget = PressureInputWidget("Pmax INPUT", "#00AA00")
        self.pmax_input_widget.pressure_logged.connect(self.on_pmax_logged)
        display_layout.addWidget(self.pmax_input_widget)

        main_layout.addLayout(display_layout)

        # === Tabbed Section ===
        self.tabs = QTabWidget()

        # Tab 1: Graph
        graph_tab = QWidget()
        graph_layout = QVBoxLayout(graph_tab)
        self.graph_widget = pg.PlotWidget()
        graph_layout.addWidget(self.graph_widget)
        self.tabs.addTab(graph_tab, "Real-Time Graph")

        # Tab 2: Hardware Details
        hardware_tab = QWidget()
        hardware_layout = QVBoxLayout(hardware_tab)
        hardware_widget = self.populate_hardware()
        hardware_layout.addWidget(hardware_widget)
        self.tabs.addTab(hardware_tab, "Hardware Setup")

        # Tab 3: Project Information
        info_tab = QWidget()
        info_layout = QVBoxLayout(info_tab)
        info_widget = self.populate_info()
        info_layout.addWidget(info_widget)
        self.tabs.addTab(info_tab, "Project Info")

        main_layout.addWidget(self.tabs, stretch=1)

        # === Status Bar ===
        self.status_bar = QStatusBar()
        self.setStatusBar(self.status_bar)
        self.status_bar.showMessage("Disconnected")

    def populate_hardware(self):
        """Populate the hardware details tab with images and descriptions"""
        scroll = QScrollArea()
        scroll.setWidgetResizable(True)
        scroll.setStyleSheet("QScrollArea { background-color: white; border: none; }")

        main_widget = QWidget()
        main_layout = QVBoxLayout(main_widget)
        main_layout.setSpacing(15)
        main_layout.setContentsMargins(30, 30, 30, 30)

        # Get the directory where this script is located
        script_dir = os.path.dirname(os.path.abspath(__file__))
        static_dir = os.path.join(script_dir, "static")

        # Helper function to create colored section
        def add_section(title, color):
            title_label = QLabel(title)
            title_label.setFont(QFont("Segoe UI", 11, QFont.Bold))
            title_label.setStyleSheet(f"color: {color}; padding: 10px 0px 5px 0px;")
            main_layout.addWidget(title_label)

        def add_line(text, color=None):
            label = QLabel(text)
            label.setFont(QFont("Segoe UI", 10))
            if color:
                label.setStyleSheet(f"color: {color};")
            else:
                label.setStyleSheet("color: #333333;")
            main_layout.addWidget(label)

        def add_separator():
            sep = QLabel("─" * 80)
            sep.setStyleSheet("color: #dddddd; padding: 10px 0px;")
            main_layout.addWidget(sep)

        def add_image(image_filename, max_width=400):
            """Add an image to the layout with max width constraint"""
            try:
                image_path = os.path.join(static_dir, image_filename)
                if not os.path.exists(image_path):
                    add_line(f"Image not found: {image_filename}", "#ff0000")
                    return
                pixmap = QPixmap(image_path)
                if not pixmap.isNull():
                    if pixmap.width() > max_width:
                        pixmap = pixmap.scaledToWidth(max_width, Qt.SmoothTransformation)
                    image_label = QLabel()
                    image_label.setPixmap(pixmap)
                    image_label.setAlignment(Qt.AlignCenter)
                    main_layout.addWidget(image_label)
                else:
                    add_line(f"Could not load image: {image_filename}", "#ff0000")
            except Exception as e:
                add_line(f"Error loading image {image_filename}: {str(e)}", "#ff0000")

        # Title
        title = QLabel("Hardware Setup")
        title.setFont(QFont("Segoe UI", 16, QFont.Bold))
        title.setAlignment(Qt.AlignCenter)
        main_layout.addWidget(title)
        add_separator()

        # Overview
        add_section("System Overview", "#0066FF")
        add_line("This 4-20mA receiver system combines three hardware components working together")
        add_line("to measure industrial current signals and process them on a PC.")
        add_separator()

        # Component 1: PAC1711 Click Board
        add_section("1. PAC1711 Click Board (Current Sensor)", "#FF6600")
        add_line("")
        add_line("The PAC1711 is a high-precision power/current sensor IC that measures current")
        add_line("flowing through a sense resistor using the I2C protocol.")
        add_line("")
        add_image("PAC1711.png", max_width=350)
        add_line("")
        add_section("Specifications:", "#FF6600")
        add_line("  • Sensing element: 2.43Ω sense resistor (on Click board)")
        add_line("  • I2C interface: 400 kHz communication speed")
        add_line("  • I2C Address: 0x45 (software configurable via A0/A1 pins)")
        add_line("  • Measurement range: 3.0 - 22.0 mA (for this 4-20mA application)")
        add_line("  • Resolution: 12-bit ADC (PAC1711 model)")
        add_line("  • Output: Voltage proportional to current (via I2C)")
        add_line("")
        add_line("How it works:")
        add_line("  → Current flows through 2.43Ω sense resistor")
        add_line("  → Creates voltage drop: V = I × 2.43Ω")
        add_line("  → PAC1711 measures this voltage")
        add_line("  → Converts to digital current value")
        add_line("  → Sends to microcontroller via I2C")
        add_separator()

        # Component 2: PIC18F57Q43 Evaluation Board
        add_section("2. PIC18F57Q43 Curiosity Nano (Microcontroller)", "#00AA00")
        add_line("")
        add_line("The PIC18F57Q43 is a 8-bit microcontroller that acts as the 'brain' of the receiver,")
        add_line("reading current data from the PAC1711 and communicating with the PC.")
        add_line("")
        add_image("PIC18F57Q43 curiosity nano.png", max_width=350)
        add_line("")
        add_section("Key Features:", "#00AA00")
        add_line("  • Architecture: 8-bit PIC microcontroller")
        add_line("  • I2C Master: Reads PAC1711 sensor at regular intervals")
        add_line("  • UART Interface: Sends data to PC via USB serial connection")
        add_line("  • Baud Rate: 115200 bps (bits per second)")
        add_line("  • Communication Interval: Every 500ms (2 measurements per second)")
        add_line("  • USB Connection: Virtual COM port for PC communication")
        add_line("")
        add_line("Its role in the system:")
        add_line("  → Reads PAC1711 current sensor via I2C")
        add_line("  → Processes measurement data")
        add_line("  → Sends formatted current values to PC via UART (USB)")
        add_line("  → Example output: 'PAC1711_GetISENSE_mA(): 12.50'")
        add_separator()

        # Component 3: Curiosity Base Board
        add_section("3. Curiosity Base Board (Expansion Interface)", "#0066FF")
        add_line("")
        add_line("The Curiosity Base Board provides connector slots for the Nano board and")
        add_line("allows connection of Click boards (like the PAC1711) in standardized slots.")
        add_line("")
        add_image("curiosity base board.png", max_width=350)
        add_line("")
        add_section("Purpose:", "#0066FF")
        add_line("  • Host interface for Curiosity Nano board (mikroBUS socket)")
        add_line("  • Standardized Click board slots for expansion modules")
        add_line("  • Power supply management for all components")
        add_line("  • Connector organization for development/prototyping")
        add_line("")
        add_line("Connection Details:")
        add_line("  → Curiosity Nano plugs into main socket")
        add_line("  → PAC1711 Click board plugs into mikroBUS slot (slot 3)")
        add_line("  → Provides I2C and power connections automatically")
        add_separator()

        # System Block Diagram
        add_section("Complete System Block Diagram", "#0066FF")
        add_line("")
        add_image("Receiver Block Diagram.png", max_width=500)
        add_line("")
        add_separator()

        # Data Flow
        add_section("Data Flow Details", "#FF0000")
        add_line("")
        add_line("Step 1: Hardware Sensing")
        add_line("  • 4-20mA signal → 2.43Ω resistor → voltage drop")
        add_line("  • Example: 12mA × 2.43Ω = 29.16mV")
        add_line("")
        add_line("Step 2: Measurement")
        add_line("  • PAC1711 measures voltage via I2C")
        add_line("  • Converts to digital current value (12.00 mA)")
        add_line("")
        add_line("Step 3: Microcontroller Processing")
        add_line("  • PIC18F57Q43 reads I2C data every 500ms")
        add_line("  • Formats: 'PAC1711_GetISENSE_mA(): 12.00'")
        add_line("")
        add_line("Step 4: Serial Transmission")
        add_line("  • Sends via UART at 115200 bps")
        add_line("  • USB connection to PC")
        add_line("")
        add_line("Step 5: PC Reception & Display")
        add_line("  • This GUI receives the data")
        add_line("  • Extracts current value: 12.00 mA")
        add_line("  • Updates real-time graph")
        add_line("  • Calculates pressure if calibrated")
        add_separator()

        # Connections
        add_section("Hardware Connections", "#0066FF")
        add_line("")
        add_line("PAC1711 ↔ PIC18F57Q43:")
        add_line("  • SCL (I2C Clock) - connected to I2C bus")
        add_line("  • SDA (I2C Data) - connected to I2C bus")
        add_line("  • GND - common ground")
        add_line("  • VCC - 3.3V power supply")
        add_line("")
        add_line("PIC18F57Q43 ↔ PC:")
        add_line("  • USB-C connection (Nano board)")
        add_line("  • Provides UART virtual COM port")
        add_line("  • Also provides power to Nano board")
        add_line("")
        add_line("Curiosity Base Board:")
        add_line("  • Powers all components via onboard regulators")
        add_line("  • Manages I2C signal routing to Click board")
        add_line("  • Provides debug/programming interface")
        add_separator()

        # Power Supply
        add_section("Power Supply Information", "#0066FF")
        add_line("")
        add_line("Power Source: USB from PC (5V)")
        add_line("  • USB-C connection to PIC18F57Q43 Nano board")
        add_line("  • Provides up to 500mA current")
        add_line("")
        add_line("Voltage Distribution:")
        add_line("  • USB 5V → Curiosity Base Board regulator")
        add_line("  • → 3.3V for PIC18F57Q43 microcontroller")
        add_line("  → 3.3V for PAC1711 sensor")
        add_line("  • All components run at 3.3V logic level")
        add_separator()

        main_layout.addStretch()

        scroll.setWidget(main_widget)

        return scroll

    def populate_info(self):
        """Populate the project information tab with simple colored text"""
        scroll = QScrollArea()
        scroll.setWidgetResizable(True)
        scroll.setStyleSheet("QScrollArea { background-color: white; border: none; }")

        main_widget = QWidget()
        main_layout = QVBoxLayout(main_widget)
        main_layout.setSpacing(15)
        main_layout.setContentsMargins(30, 30, 30, 30)

        # Helper function to create colored section
        def add_section(title, color):
            title_label = QLabel(title)
            title_label.setFont(QFont("Segoe UI", 11, QFont.Bold))
            title_label.setStyleSheet(f"color: {color}; padding: 10px 0px 5px 0px;")
            main_layout.addWidget(title_label)

        def add_line(text, color=None):
            label = QLabel(text)
            label.setFont(QFont("Segoe UI", 10))
            if color:
                label.setStyleSheet(f"color: {color};")
            else:
                label.setStyleSheet("color: #333333;")
            main_layout.addWidget(label)

        def add_link(text, url):
            link_label = QLabel(f'<a href="{url}" style="color: #0066FF; text-decoration: underline;">{text}</a>')
            link_label.setOpenExternalLinks(True)
            link_label.setFont(QFont("Segoe UI", 10))
            main_layout.addWidget(link_label)

        def add_separator():
            sep = QLabel("─" * 80)
            sep.setStyleSheet("color: #dddddd; padding: 10px 0px;")
            main_layout.addWidget(sep)

        # Title
        title = QLabel("PAC1711 4-20mA Receiver")
        title.setFont(QFont("Segoe UI", 16, QFont.Bold))
        title.setAlignment(Qt.AlignCenter)
        main_layout.addWidget(title)
        add_separator()

        # Overview
        add_section("System Overview", "#0066FF")
        add_line("This system measures 4-20mA industrial current signals and converts them")
        add_line("to pressure values using a linear calibration formula.")
        add_separator()

        # What it does
        add_section("How It Works", "#0066FF")
        add_line("")
        add_line("1. Hardware (on the PIC18F57Q43 Microcontroller Board):")
        add_line("   • The PAC1711 sensor measures current flowing through a 2.43Ω resistor")
        add_line("   • Current measurement range: 4-20mA (industrial standard)")
        add_line("   • The PIC18F57Q43 microcontroller reads this current via I2C connection")
        add_line("")
        add_line("2. Communication (USB to PC):")
        add_line("   • Microcontroller sends current data to PC via UART (serial port)")
        add_line("   • Baud rate: 115200 (fast serial communication)")
        add_line("   • Data format: \"PAC1711_GetISENSE_mA(): 12.50\"")
        add_line("")
        add_line("3. Software (this GUI on your PC):")
        add_line("   • Receives current values from the microcontroller")
        add_line("   • You enter Pmin and Pmax calibration values (pressure at 4mA and 20mA)")
        add_line("   • Calculates pressure using: P = m·I + b")
        add_line("   • Displays current and calculated pressure in real-time")
        add_line("   • Plots both values on a live graph")
        add_separator()

        # Device roles
        add_section("Hardware Components", "#0066FF")
        add_line("")
        add_line("PIC18F57Q43 (Microcontroller):")
        add_line("   • The \"brain\" of the hardware")
        add_line("   • Reads current measurements from PAC1711 sensor via I2C")
        add_line("   • Sends data to PC via UART serial connection")
        add_line("   • Runs every 500ms to continuously measure current")
        add_line("")
        add_line("PAC1711 (Current Sensor):")
        add_line("   • Measures the 4-20mA current flowing through the 2.43Ω sense resistor")
        add_line("   • Converts current to a voltage reading")
        add_line("   • Returns the data to microcontroller via I2C")
        add_line("   • Acts as a \"current to voltage converter\"")
        add_separator()

        # Formula
        add_section("Pressure Calculation Formula", "#FF0000")
        add_line("P = m·I + b", "#FF0000")
        add_line("")
        add_line("Where:")
        add_line("  m = (Pmax - Pmin) / 16     [Slope]")
        add_line("  b = Pmin - m·4             [Intercept]")
        add_line("  I = Current (mA)           [From PAC1711]")
        add_line("  P = Pressure (PSI)         [Calculated]")
        add_separator()

        # Calibration
        add_section("Calibration Points (4-20mA)", "#0066FF")
        add_line("4 mA   →  Pmin (minimum pressure)", "#CCAA00")
        add_line("12 mA  →  (Pmin + Pmax) / 2", "#0066FF")
        add_line("20 mA  →  Pmax (maximum pressure)", "#00AA00")
        add_separator()

        # Colors
        add_section("Color Legend", "#0066FF")
        add_line("🔵 Blue (#0066FF)    = Current (Auto)", "#0066FF")
        add_line("🔴 Red (#FF0000)     = Calculated Pressure (Auto)", "#FF0000")
        add_line("🟡 Yellow (#CCAA00)  = Pmin Input (Manual)", "#CCAA00")
        add_line("🟢 Green (#00AA00)   = Pmax Input (Manual)", "#00AA00")
        add_separator()

        # Device Info
        add_section("Device Information", "#0066FF")
        add_line("Microcontroller:   PIC18F57Q43 Curiosity Nano")
        add_line("Sensor:            PAC1711 Click Board")
        add_line("Sense Resistor:    2.43Ω")
        add_line("I2C Address:       0x45")
        add_line("I2C Speed:         400 kHz")
        add_line("UART Baud:         115200")
        add_line("Current Range:     3.0 - 22.0 mA")
        add_separator()

        # Example
        add_section("Example", "#FF0000")
        add_line("Given: Pmin = 0 PSI, Pmax = 50 PSI, I = 12 mA")
        add_line("")
        add_line("m = (50 - 0) / 16 = 3.125")
        add_line("b = 0 - (3.125 × 4) = -12.5")
        add_line("P = 3.125 × 12 - 12.5 = 25.0 PSI", "#FF0000")

        main_layout.addStretch()

        # Bottom Section: Author, Contacts, Reference Design
        add_separator()

        add_section("Developer", "#0066FF")
        add_line("Akanksha Tripathi")
        add_line("")

        add_section("For More Information related to Receiver contact", "#0066FF")
        add_line("Akanksha Tripathi")
        add_line("akanksha.tripathi@microchip.com")
        add_line("")

        add_section("For More Information related to Transmitter contact", "#0066FF")
        add_line("Joshua Smith")
        add_line("joshua.smith@microchip.com")
        add_line("")
        add_line("Sultan Al Niyadi")
        add_line("sultan.alniyadi@microchip.com")
        add_line("")

        add_section("Reference", "#0066FF")
        add_link("https://www.microchip.com/en-us/tools-resources/reference-designs/dac-based-4-20-ma-current-loop-reference-design",
                 "https://www.microchip.com/en-us/tools-resources/reference-designs/dac-based-4-20-ma-current-loop-reference-design")

        scroll.setWidget(main_widget)

        return scroll

    def setup_graph(self):
        """Configure the pyqtgraph plot with dual Y-axis"""
        self.graph_widget.setBackground('#ffffff')
        self.graph_widget.showGrid(x=True, y=True, alpha=0.3)
        self.graph_widget.setLabel('bottom', 'Time', units='s')
        self.graph_widget.setLabel('left', 'Current', units='mA', color='#0066FF')
        self.graph_widget.setXRange(0, GRAPH_WINDOW)
        self.graph_widget.setYRange(0, 25)

        # Current plot (left Y-axis) - blue
        self.current_curve = self.graph_widget.plot(
            pen=pg.mkPen(color='#0066FF', width=2),
            name='Current (mA)'
        )

        # Create second Y-axis for pressure
        self.pressure_axis = pg.ViewBox()
        self.graph_widget.scene().addItem(self.pressure_axis)
        self.graph_widget.getAxis('right').linkToView(self.pressure_axis)
        self.pressure_axis.setXLink(self.graph_widget)

        # Configure right axis
        self.graph_widget.getAxis('right').setLabel('Pressure', units='PSI', color='#FF0000')
        self.graph_widget.getAxis('right').show()

        # Pmin plot (right Y-axis) - yellow
        self.pmin_curve = pg.PlotCurveItem(
            pen=pg.mkPen(color='#CCAA00', width=2)
        )
        self.pressure_axis.addItem(self.pmin_curve)

        # Pmax plot (right Y-axis) - green
        self.pmax_curve = pg.PlotCurveItem(
            pen=pg.mkPen(color='#00AA00', width=2)
        )
        self.pressure_axis.addItem(self.pmax_curve)

        # Calculated pressure plot (right Y-axis) - red
        self.pressure_calc_curve = pg.PlotCurveItem(
            pen=pg.mkPen(color='#FF0000', width=2)
        )
        self.pressure_axis.addItem(self.pressure_calc_curve)

        # Handle view resize
        self.graph_widget.getViewBox().sigResized.connect(self.update_views)

        # Legend
        self.graph_widget.addLegend()

    def update_views(self):
        """Keep the pressure ViewBox synchronized with the main plot"""
        self.pressure_axis.setGeometry(self.graph_widget.getViewBox().sceneBoundingRect())
        self.pressure_axis.linkedViewChanged(self.graph_widget.getViewBox(), self.pressure_axis.XAxis)

    def refresh_ports(self):
        """Scan for available COM ports"""
        self.port_combo.clear()
        ports = serial.tools.list_ports.comports()
        for port in ports:
            self.port_combo.addItem(f"{port.device} - {port.description}", port.device)

        if self.port_combo.count() == 0:
            self.port_combo.addItem("No ports found", None)

    def toggle_connection(self):
        """Connect or disconnect from serial port"""
        if self.is_connected:
            self.disconnect_serial()
        else:
            self.connect_serial()

    def connect_serial(self):
        """Establish serial connection"""
        port = self.port_combo.currentData()
        if port is None:
            self.status_bar.showMessage("No port selected")
            return

        baud = int(self.baud_combo.currentText())

        self.serial_reader = SerialReader(self.serial_signals)
        self.serial_reader.connect(port, baud)
        self.serial_reader.start()

    def disconnect_serial(self):
        """Close serial connection"""
        if self.serial_reader:
            self.serial_reader.disconnect()

    def on_connected(self):
        """Handle successful connection"""
        self.is_connected = True
        self.connect_btn.setText("Disconnect")
        self.connect_btn.setStyleSheet("font-weight: bold; background-color: #004400;")
        self.port_combo.setEnabled(False)
        self.baud_combo.setEnabled(False)
        self.status_bar.showMessage("Connected")

    def on_disconnected(self):
        """Handle disconnection"""
        self.is_connected = False
        self.connect_btn.setText("Connect")
        self.connect_btn.setStyleSheet("font-weight: bold;")
        self.port_combo.setEnabled(True)
        self.baud_combo.setEnabled(True)
        self.status_bar.showMessage("Disconnected")

    def on_serial_error(self, error_msg):
        """Handle serial errors"""
        self.status_bar.showMessage(f"Error: {error_msg}")

    def on_data_received(self, current_mA):
        """Process incoming current reading"""
        timestamp = time.time()
        self.current_buffer.append((timestamp, current_mA))
        self.sample_count += 1
        self.last_current = current_mA

        # Update current display
        self.current_display.set_value(current_mA)

        # Calculate and display pressure if Pmin and Pmax are set
        pressure = calculate_pressure(current_mA, self.last_pmin, self.last_pmax)
        if pressure is not None:
            self.pressure_calc_buffer.append((timestamp, pressure))
            self.last_pressure_calc = pressure
            self.pressure_calc_display.set_value(pressure)

        # Update status
        self.status_bar.showMessage(
            f"Connected | Samples: {self.sample_count} | Current: {current_mA:.2f} mA"
        )

    def on_pmin_logged(self, pressure):
        """Process manually entered Pmin value with validation"""
        # Check: Pmin >= 0
        if pressure < 0:
            self.pmin_input_widget.show_error("Error: Pmin < 0")
            self.status_bar.showMessage("Error: Pmin must be >= 0")
            return

        # Check: Pmin < Pmax (if Pmax is set)
        if self.last_pmax is not None and pressure >= self.last_pmax:
            self.pmin_input_widget.show_error("Error: Pmin >= Pmax")
            self.status_bar.showMessage("Error: Pmin must be less than Pmax")
            return

        timestamp = time.time()
        self.pmin_buffer.append((timestamp, pressure))
        self.last_pmin = pressure
        self.pmin_input_widget.set_logged_value(pressure)
        self.pmin_input_widget.last_logged_label.setStyleSheet("color: #666666; font-size: 11px;")
        self.update_pressure_axis_range()
        self.status_bar.showMessage(
            f"Pmin logged: {pressure:.2f} PSI | Samples: {self.sample_count}"
        )
        # Clear calculated pressure buffer when calibration changes
        self.pressure_calc_buffer.clear()

    def on_pmax_logged(self, pressure):
        """Process manually entered Pmax value with validation"""
        # Check: Pmax <= 50
        if pressure > 50:
            self.pmax_input_widget.show_error("Error: Pmax > 50")
            self.status_bar.showMessage("Error: Pmax must be <= 50")
            return

        # Check: Pmax > Pmin (if Pmin is set)
        if self.last_pmin is not None and pressure <= self.last_pmin:
            self.pmax_input_widget.show_error("Error: Pmax <= Pmin")
            self.status_bar.showMessage("Error: Pmax must be greater than Pmin")
            return

        timestamp = time.time()
        self.pmax_buffer.append((timestamp, pressure))
        self.last_pmax = pressure
        self.pmax_input_widget.set_logged_value(pressure)
        self.pmax_input_widget.last_logged_label.setStyleSheet("color: #666666; font-size: 11px;")
        self.update_pressure_axis_range()
        self.status_bar.showMessage(
            f"Pmax logged: {pressure:.2f} PSI | Samples: {self.sample_count}"
        )
        # Clear calculated pressure buffer when calibration changes
        self.pressure_calc_buffer.clear()

    def update_pressure_axis_range(self):
        """Auto-adjust pressure Y-axis based on all pressure values (manual + calculated)"""
        all_pressures = []
        if len(self.pmin_buffer) > 0:
            all_pressures.extend([p for _, p in self.pmin_buffer])
        if len(self.pmax_buffer) > 0:
            all_pressures.extend([p for _, p in self.pmax_buffer])
        if len(self.pressure_calc_buffer) > 0:
            all_pressures.extend([p for _, p in self.pressure_calc_buffer])

        if len(all_pressures) == 0:
            return

        p_min = min(all_pressures)
        p_max = max(all_pressures)

        # Add 10% margin
        margin = max((p_max - p_min) * 0.1, 1.0)  # At least 1 PSI margin
        self.pressure_axis.setYRange(p_min - margin, p_max + margin)

    def update_graph(self):
        """Update the graph with buffered data"""
        now = time.time()
        elapsed = now - self.start_time  # Time since start (positive)

        # Update X-axis range to scroll with time
        if elapsed > GRAPH_WINDOW:
            self.graph_widget.setXRange(elapsed - GRAPH_WINDOW, elapsed)
        else:
            self.graph_widget.setXRange(0, GRAPH_WINDOW)

        # Update current curve (automatic data)
        if len(self.current_buffer) >= 2:
            times = []
            currents = []

            for timestamp, current in self.current_buffer:
                rel_time = timestamp - self.start_time  # Positive time since start
                if rel_time >= elapsed - GRAPH_WINDOW:
                    times.append(rel_time)
                    currents.append(current)

            if len(times) > 0:
                self.current_curve.setData(times, currents)

        # Update Pmin curve (manual entries as stepped line)
        self._update_pressure_curve(self.pmin_buffer, self.last_pmin, self.pmin_curve, elapsed)

        # Update Pmax curve (manual entries as stepped line)
        self._update_pressure_curve(self.pmax_buffer, self.last_pmax, self.pmax_curve, elapsed)

        # Update calculated pressure curve (automatic, continuous line)
        if len(self.pressure_calc_buffer) >= 2:
            times = []
            pressures = []

            for timestamp, pressure in self.pressure_calc_buffer:
                rel_time = timestamp - self.start_time  # Positive time since start
                if rel_time >= elapsed - GRAPH_WINDOW:
                    times.append(rel_time)
                    pressures.append(pressure)

            if len(times) > 0:
                self.pressure_calc_curve.setData(times, pressures)

    def _update_pressure_curve(self, buffer, last_value, curve, elapsed):
        """Helper to update a pressure curve as stepped line - keeps full history"""
        if len(buffer) < 1 and last_value is None:
            return

        times = []
        pressures = []
        window_start = max(0, elapsed - GRAPH_WINDOW)

        # Build stepped line from all pressure entries
        for i, (timestamp, pressure) in enumerate(buffer):
            rel_time = timestamp - self.start_time  # Positive time since start

            # For points older than window, clamp to left edge
            if rel_time < window_start:
                # Only include if next point is within window
                if i < len(buffer) - 1:
                    next_rel_time = buffer[i + 1][0] - self.start_time
                    if next_rel_time >= window_start:
                        times.append(window_start)
                        pressures.append(pressure)
                continue

            times.append(rel_time)
            pressures.append(pressure)

            # Extend to next point (stepped line)
            if i < len(buffer) - 1:
                next_time = buffer[i + 1][0] - self.start_time
                if next_time > window_start:
                    times.append(next_time)
                    pressures.append(pressure)

        # Extend last pressure value to current time
        if last_value is not None:
            if len(times) == 0:
                # All points are before window, but show last value across entire window
                times.append(window_start)
                pressures.append(last_value)
            times.append(elapsed)  # Now
            pressures.append(last_value)

        if len(times) > 0:
            curve.setData(times, pressures)

    def closeEvent(self, event):
        """Clean up on window close"""
        if self.serial_reader:
            self.serial_reader.disconnect()
        self.update_timer.stop()
        event.accept()


def main():
    try:
        app = QApplication(sys.argv)

        # Dark theme
        app.setStyle('Fusion')

        window = PAC1711GUI()
        window.show()

        sys.exit(app.exec())
    except Exception as e:
        print(f"ERROR: {e}")
        print(f"Type: {type(e)}")
        import traceback
        traceback.print_exc()
        input("Press Enter to exit...")


if __name__ == "__main__":
    main()
