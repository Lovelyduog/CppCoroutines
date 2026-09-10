# CppCoroutines

A personal learning project for C++20 coroutines, evolving toward a homegrown coroutine library.

## 提问方式（用户偏好）

凡是需要用户拍板的问题，一律优先使用 `AskUserQuestion` 工具以结构化选项形式提出：

- 推荐答案放第一个选项，标注「（推荐）」
- 每题选项 2~4 个，超出时拆成多题或用「Other」兜底
- 纯开放式讨论（无收敛候选）不强制套用，但也尽量先给选项

## Agent skills

### Issue tracker

Issues are tracked as local markdown files under `.scratch/<feature>/`. See `docs/agents/issue-tracker.md`.

### Triage labels

The default five triage roles are used as-is (`needs-triage`, `needs-info`, `ready-for-agent`, `ready-for-human`, `wontfix`). See `docs/agents/triage-labels.md`.

### Domain docs

Single-context layout: one `CONTEXT.md` and `docs/adr/` at the repo root. See `docs/agents/domain.md`.
