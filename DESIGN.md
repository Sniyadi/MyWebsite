---
name: Sultan Al Niyadi Portfolio
description: High-end dark engineering aesthetic for applications engineering, silicon systems, and engineering management showcase
colors:
  bg-primary: "#080b11"
  bg-secondary: "#0e1420"
  bg-tertiary: "#141d2d"
  accent-cyan: "#00e5ff"
  accent-blue: "#3b82f6"
  accent-emerald: "#10b981"
  accent-amber: "#f59e0b"
  accent-indigo: "#6366f1"
  text-primary: "#f8fafc"
  text-secondary: "#94a3b8"
  text-muted: "#64748b"
  border-subtle: "rgba(255, 255, 255, 0.08)"
  border-accent: "rgba(0, 229, 255, 0.35)"
typography:
  display:
    fontFamily: "Outfit, -apple-system, sans-serif"
    fontSize: "3.25rem"
    fontWeight: 800
    lineHeight: 1.15
    letterSpacing: "-0.02em"
  heading:
    fontFamily: "Outfit, -apple-system, sans-serif"
    fontSize: "2rem"
    fontWeight: 700
    lineHeight: 1.25
    letterSpacing: "-0.01em"
  body:
    fontFamily: "Outfit, -apple-system, sans-serif"
    fontSize: "1rem"
    fontWeight: 400
    lineHeight: 1.65
    letterSpacing: "normal"
  mono:
    fontFamily: "JetBrains Mono, monospace"
    fontSize: "0.82rem"
    fontWeight: 500
    lineHeight: 1.4
    letterSpacing: "0.05em"
rounded:
  sm: "8px"
  md: "12px"
  lg: "18px"
  xl: "24px"
  full: "9999px"
spacing:
  xs: "4px"
  sm: "8px"
  md: "16px"
  lg: "24px"
  xl: "32px"
  2xl: "48px"
  3xl: "64px"
components:
  button-primary:
    backgroundColor: "{colors.accent-cyan}"
    textColor: "{colors.bg-primary}"
    rounded: "{rounded.sm}"
    padding: "8px 16px"
  button-secondary:
    backgroundColor: "rgba(255, 255, 255, 0.05)"
    textColor: "{colors.text-primary}"
    rounded: "{rounded.sm}"
    padding: "8px 16px"
  card-glass:
    backgroundColor: "rgba(16, 24, 39, 0.65)"
    textColor: "{colors.text-primary}"
    rounded: "{rounded.xl}"
    padding: "36px"
  badge:
    backgroundColor: "rgba(0, 229, 255, 0.08)"
    textColor: "{colors.accent-cyan}"
    rounded: "{rounded.full}"
    padding: "6px 14px"
---

# Design System Specification

## Overview
A technical, refined dark-mode design system tailored for semiconductor applications engineering, silicon integration, and executive engineering management. The visual world projects authoritative competence, zero fluff, clean mathematical hierarchies, and atmospheric glow inspired by modern laboratory instruments and hardware testing interfaces.

## Colors
- **Core Dark Canvas**: `#080b11` (Primary background) providing deep contrast for technical assets; `#0e1420` and `#141d2d` for elevated layers and surfaces.
- **Accents**:
  - **Electric Cyan (`#00e5ff`)**: Primary accent used for brand chips, active indicators, interactive CTAs, and key metrics.
  - **Tech Blue (`#3b82f6`)**: Complementary gradient accent for secondary interactive depth.
  - **Emerald (`#10b981`)**: Used for active status indicator dots and hardware verification milestones.
  - **Amber (`#f59e0b`)**: Used for Senior Capstone and honors achievements.
  - **Indigo (`#6366f1`)**: Used for systems engineering and literature review elements.
- **Typography Colors**: `#f8fafc` (high-contrast primary), `#94a3b8` (scannable secondary), `#64748b` (metadata & captions).

## Typography
- **Headings**: `Outfit` — architectural, clean geometric letterforms delivering high-impact executive headlines.
- **Body Text**: `Outfit` — modern, distinctive grotesque offering authentic personality, crisp reading, and high credibility.
- **Code & Specs**: `JetBrains Mono` — monospaced precision applied to dates, technical parameters, and category tags.

## Layout
- **Grid Structure**: 1200px container width with 24px horizontal gutters.
- **Background Texture**: 40px subtle grid background evoking engineering schematics and laboratory benches.
- **Hierarchical Spacing**: 96px vertical section spacing on desktop, collapsing to 64px on mobile viewports.

## Elevation & Depth
- **Glassmorphism**: Translucent card backgrounds (`rgba(16, 24, 39, 0.65)`) with `backdrop-filter: blur(16px)`.
- **Subtle Borders**: 1px crisp borders (`rgba(255, 255, 255, 0.08)`), transitioning to `rgba(0, 229, 255, 0.35)` on hover.
- **Atmospheric Glows**: Radial cyan and indigo gradient diffusions softly illuminating viewports without visual distraction.

## Shapes
- **Corner Radii**:
  - `8px` for buttons, chips, and input fields.
  - `12px` to `18px` for nested panels, category cards, and timeline contents.
  - `24px` for outer project containers, hero portrait frame, and contact wrapper.
  - `9999px` (Pill) for status badges, tags, and category filter buttons.

## Components
- **Navbar**: Sticky frosted glass navigation with brand monogram chip (`SN`) and quick access to CV download and LinkedIn.
- **Hero Unit**: Asymmetrical grid balancing authoritative headline copy against a glowing portrait frame and live status badges.
- **Timeline**: Chronological vertical axis with circular iconography and tag rows.
- **Project Cards**: Two-tier grid featuring flagship system across the top and specialized sub-projects in a balanced 3-column row.
- **Skills Matrix**: Interactive category pill filter with instantaneous CSS transitions.

## Do's and Don'ts
- **Do**:
  - Keep typography crisp, scannable, and evidence-grounded.
  - Use monospaced tags (`JetBrains Mono`) for specific EDA tools, firmware, and protocols.
  - Maintain high contrast ratios (> 4.5:1) for all body text against dark backgrounds.
- **Don't**:
  - Never use generic purple gradients or saturated saturated neon blocks.
  - Never sacrifice legibility for decorative effects.
  - Avoid noisy animations; use subtle, purposeful transitions (0.25s ease).
