# perception-core

Radar / perception core — produces the detected-object interface.

## Role

Produces `GenObjectList` (objects) from sensor input. First component to validate
the standard build pattern (Conan + preset + `build.bat`).

## Local constraints

- **"objects" never "tracks"** — `GenObject`/`GenObjectList`, topic `/objects`
  (R-NAME-1).
- **Not yet wired into `sil`** — no real Conan package for it yet (R-SIL-2).
- Legacy **PascalCase file names stay** until touched for other reasons — do not
  mass-rename (R-NAME-5).
- Accepts `-P/--project` for a uniform call shape but has no project-scoped
  calibration of its own yet. Header `COMPONENT: PERCEPTION_CORE`.

## AI operational layer — root-canonical

Part of `1v-superproject`. Cross-cutting rules/skills/templates/workflows live
once at the superproject root `.claude/` (spec:
`docs/ai_operational_layer_spec.md`). Load `../../.claude/rules/*` + the matching
`skills/*`; do not duplicate them here. This file holds only what is local to
`perception-core`.
