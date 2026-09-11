# raygui update: `GuiTextInputBox()` signature change

When `raylib`/`raygui` were vendored as submodules (`lib/raylib`, `lib/raygui`), the
newer `raygui` redesigned `GuiTextInputBox()`, breaking the existing call in
`src/ui.cpp`.

## What changed

Old raygui returned the pressed-button index directly, with this parameter order:

```c
GuiTextInputBox(bounds, title, message, btnText, text, textSize, secretViewActive)
```

New raygui (`lib/raygui/src/raygui.h:863`) reordered the parameters and split the
result into two pieces:

```c
int GuiTextInputBox(Rectangle bounds, const char *title, const char *message,
                     char *text, int textSize, const char *btnText,
                     int *btnActive, bool *secretViewActive);
```

- **Return value** is now just `RESULT_PRESSED` (1) or `RESULT_NONE` (0) — whether
  *any* interaction closed the box (a listed button, or the window's own close
  icon).
- **`btnActive`** (new out-parameter) reports *which* button closed it — `0` if
  closed via the window's close icon, `1..n` indexing into the `;`-separated
  `btnText` list.

The old call in `ui.cpp` passed arguments in the old order and never supplied the
new `btnActive` out-parameter, so it no longer matched the header and failed to
compile.

## The fix (`src/ui.cpp`)

1. Reordered the call to match the new signature:
   `GuiTextInputBox(nbounds, title, message, name, 255, "Ok", &btnActive, &secret_view)`.
2. Added a local `int btnActive` to receive which button was pressed.
3. Rewrote `GetNameFromUser()` to translate the new two-piece result back into the
   single-int contract `main.cpp` already relies on (`-1` = still waiting,
   `1` = "Ok" clicked):
   - `result == RESULT_NONE` → return `-1` (box still open).
   - otherwise → return `btnActive` (`1` for the single "Ok" button).
4. Removed the stray duplicate `GuiTextInputBox` prototype that had been pasted
   below the call for reference — it's already declared in `raygui.h`, and the
   leftover copy used the old parameter order.

`main.cpp`'s other Gui calls (`GuiButton`, `GuiIconText`) were checked against the
vendored header and are unchanged, so they needed no updates.

Verified with `cmake --build build` — compiles and links cleanly.
