# WINDOWNAV Layer Design

Modal keyboard layer for tiling window manager navigation on a ZSA Moonlander
with a Dvorak-ish layout. Designed to work across niri (Linux) and Aerospace
(macOS), and to be forward-compatible with other tiling WMs.

## Core Model

The layer is toggled on/off with left thumb 3. While active, all keys are
remapped for window management. Exiting the layer returns to normal keyboard
operation.

Two independent axes control directional operations:

| Axis   | Mechanism              | Default   |
|--------|------------------------|-----------|
| Scope  | Modal/sticky key       | Window    |
| Action | Modifier held with dir | Navigate  |

### Scopes

Four scopes form a hierarchy. The scope determines the coordinate space in
which directional operations act.

| Scope     | Navigate means                    | Move means                                   |
|-----------|-----------------------------------|----------------------------------------------|
| Monitor   | Focus shifts to adjacent monitor  | Send focused window to adjacent monitor      |
| Workspace | Focus shifts to adjacent workspace| Send focused window to adjacent workspace    |
| Window    | Focus shifts to adjacent window   | Reorder window position within workspace     |
| Pane      | Focus shifts to adjacent pane     | Reorder pane within window layout            |

Scope is selected by pressing a sticky key. It persists until changed or the
layer is exited. Re-entering the layer always resets scope to window (default).

### Actions on Directional Keys

| Action   | Modifier | Notes                              |
|----------|----------|------------------------------------|
| Navigate | bare     | Most common, should be effortless  |
| Move     | shift    | Natural "stronger navigate"        |
| Resize   | ctrl     | Held modifier; fine for short bursts|

## Directional Keys

### Primary: 4-directional, scope-dependent

```
      c (up)
h (left)  t (down)  n (right)
```

These mirror the existing NAV layer arrangement. All three action modifiers
(bare/shift/ctrl) apply.

### Tabs: 2-directional, unscoped

| Key | Action          |
|-----|-----------------|
| `g` | Tab left        |
| `r` | Tab right       |
| `G` | Move tab left   |
| `R` | Move tab right  |

Ctrl+g / ctrl+r also map to move (since resize is meaningless for tabs).

Tab keys are fully independent of the current scope. They always operate on
tabs regardless of whether scope is set to window, workspace, etc.

Rationale: tabs are a concept that only exists within certain applications
(browsers, tmux, terminal emulators). They don't participate in the
monitor/workspace/window/pane hierarchy, but they need 1-dimensional
navigation. `g` and `r` correspond to page-up and page-down positions in the
existing NAV layer.

## Scope Keys

Sticky. Press once to switch; persists until changed or layer is exited.

| Key | Scope            | Mnemonic     | Hand  |
|-----|------------------|--------------|-------|
| `w` | Window (default) | **w**indow   | right |
| `s` | Workspace        | **s**pace    | right |
| `p` | Pane             | **p**ane     | left  |
| `o` | Monitor          | **o**utput   | left  |

Right-hand placement for some scope keys is intentional: the left hand may be
positioning for shift/ctrl, so right-hand scope keys let you set scope before
grabbing the modifier.

## Scoped One-Shot Actions

These are single-keypress operations that respect the current scope.

| Key | Action         | Mnemonic        |
|-----|----------------|-----------------|
| `f` | Fullscreen/zoom| **f**ullscreen   |
| `v` | Float toggle   | ho**v**er        |
| `x` | Close          | e**x**it         |
| `a` | Create/add new | **a**dd          |
| `z` | Zoom (max width)| **z**oom        |

Scope interaction:

- **Fullscreen:** window scope = fullscreen, pane scope = pane zoom (e.g.
  tmux zoom).
- **Float:** window scope = toggle floating window, pane scope = toggle
  floating pane (if supported).
- **Close:** window scope = close window, pane scope = close pane/tab.
- **Create:** window scope = new terminal window, pane scope = new pane/tab.
- At scopes where an action doesn't make sense (e.g. "create monitor"), the
  key is a no-op or mapped to a harmless shortcut to allow for future WM
  support (e.g. "create workspace" for WMs that support it).

## Scoped Prefix Actions

Consume and emit are one-shot prefix keys followed by a direction.

| Prefix | Action  | Mnemonic     |
|--------|---------|--------------|
| `i`    | Consume | **i**ngest   |
| `e`    | Emit    | **e**mit     |

After pressing `i` or `e`, press a direction key to specify the direction of
the operation. For example:

- `in` = consume window from right into current column (niri)
- `ih` = consume window from left (if supported)
- `p ir` = consume next tab into current pane group (tmux, pane scope)
- `en` = emit current window to new column on right (niri)

Directions that aren't supported by the current WM/app are simply no-ops.

## Absolute Workspace Access

Accessed via the NUM momentary hold key (same key used for the numpad layer
in normal operation). While in WINDOWNAV and holding NUM:

| Keys      | Action                      |
|-----------|-----------------------------|
| `0`-`9`   | Switch to workspace N       |
| shift+`0`-`9` | Send focused window to workspace N |

The numpad key positions are reused from the existing NUM layer, so muscle
memory carries over. WMs that only support workspaces 1-9 will simply ignore
workspace 0.

## Launcher Prefix

`space` (left thumb 1) is a one-shot prefix for launcher/picker operations.
Press space, then a mnemonic key to launch.

Launchers open a picker or prompt, the user makes a selection, and the picker
dismisses. These map directly to host keybinds (e.g. `alt+p` for app
launcher).

| Sequence    | Action         | Notes                     |
|-------------|----------------|---------------------------|
| `space` `p` | App launcher   | **p**rograms              |
| `space` `s` | SSH prompt     | **s**sh                   |
| `space` `t` | OATH tokens    | **t**okens                |

The specific set of launchers is machine-dependent. Additional launchers can
be added to unused keys under the space prefix.

## Scratchpad Prefix

`enter` (right thumb 3) is a one-shot prefix for scratchpad operations.
Press enter, then a mnemonic key to toggle.

Scratchpads toggle the visibility of a persistent application (dropdown
terminal, notes app, etc.). These also map to host keybinds.

| Sequence     | Action         | Notes                     |
|--------------|----------------|---------------------------|
| `enter` `n`  | Notes          | **n**otes (Obsidian)      |
| `enter` `t`  | Terminal       | **t**erminal (dropdown)   |
| `enter` `l`  | LLM/agent      | **l**lm                   |
| `enter` `c`  | Calculator     | **c**alc                  |

The specific set of scratchpads is machine-dependent.

## Window Switcher (Alt-Tab)

A sub-layer that emulates the OS window switcher.

**Entry:**
- `backspace` (right thumb 2) in WINDOWNAV: registers alt (held virtually),
  sends tab, enters switcher sub-layer. Selects the most recent window.
- `tab` (right thumb 1) in WINDOWNAV: registers alt, sends shift+tab, enters
  switcher sub-layer. Selects in reverse order.

**While in switcher sub-layer:**
- `backspace` = send tab (cycle forward, alt still held)
- `tab` = send shift+tab (cycle backward, alt still held)
- `enter` or `escape` = unregister alt (confirms selection), return to
  WINDOWNAV
- Toggle key (left thumb 3) = unregister alt, exit WINDOWNAV entirely

All other keys are no-ops in the switcher sub-layer. The OS is in switcher
mode; sending unrelated keybinds would be harmful.

**macOS note:** the switcher uses cmd-tab, not alt-tab. The implementation
must account for OS detection, similar to the existing ctrl/cmd swap logic.

## Mode Management

| Key            | Action                                  |
|----------------|-----------------------------------------|
| Left thumb 3   | Toggle WINDOWNAV on/off                 |
| Scope keys     | Switch scope (sticky)                   |
| Layer re-entry | Always resets scope to window (default) |

## LED Feedback

Each scope gets a distinct LED color scheme, consistent with the existing
per-layer LED maps. This provides constant visual feedback for the current
scope, which is the only persistent modal state to track (actions are
transient modifiers).

## Key Map Summary

### Left hand

```
 '  ,  .  p  y          p = pane scope
 a  o  e  u  i          o = monitor scope, a = add, e = emit, i = ingest
 ;  q  x  j  k          x = close
```

### Right hand

```
 f  g  c  r  l          f = fullscreen, g = tab-left, c = up, r = tab-right
 d  h  t  n  s          h = left, t = down, n = right, s = workspace scope
 b  m  w  v  z          w = window scope, v = float
```

### Thumb cluster

```
Left:  space (launcher prefix)  shift (move modifier)  TOGGLE (enter/exit)
Right: tab (switcher-back)      backspace (switcher)   enter (scratchpad prefix)
```

### Unassigned keys

Left: `'`, `,`, `.`, `y`, `u`, `;`, `q`, `j`, `k`
Right: `d`, `l`, `b`, `m`

These are available for future operations.

## Full Example Sequences

```
cccc              navigate up 4 windows
s cccc            navigate up 4 workspaces
p cccc            navigate up 4 panes
o nn              navigate right 2 monitors
HHH               move window left 3 within workspace
p CC              move pane up 2 within window
s C               move window to workspace above
o N               move window to right monitor
HHH nnn           move window left 3, then navigate right 3
ctrl-n x5         grow window rightward 5 times
p ctrl-t x3       shrink pane downward 3 times
f                 fullscreen window
p f               zoom pane (e.g. tmux zoom)
x                 close window
p x               close pane
a                 new terminal window
p a               new pane/tab
in                consume window from right (niri column ingest)
p ir              consume next tab into pane group (tmux)
en                emit window to new column right (niri)
rr                navigate 2 tabs right
GG                move tab left 2 positions
[NUM hold] 5      switch to workspace 5
[NUM hold] S-3    send window to workspace 3
space p           app launcher
enter t           toggle dropdown terminal
backspace         alt-tab to previous window
  backspace       cycle to next in switcher
  tab             cycle to previous in switcher
  enter           confirm selection, back to WINDOWNAV
[toggle]          exit to normal mode
```
