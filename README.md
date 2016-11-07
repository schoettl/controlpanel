Control Panel
=============

It's an easily customizable system control panel.
It comes with a tray icon to show the panel if it's hidden.

It's written in C++/Qt5.

Example configuration file `~/.config/controlpanel/buttons.conf`:

```
# This is a comment line.

# Columns are separated with a tab:

# - Button caption
# - Primary button shell command
# - Shell command to determine button visibility

# Don't forget the trailing "&" in the primary command
# to run a command in background.

# :quit and :close are special commands.

Herunterfahren	xmessage shutdown -h now &	true
Tastatur	florence &
Netzwerk	nm-connection-editor &
Fernwartung aktivieren	xmessage autossh ...	! ps -C autossh
Fernwartung deaktivieren	florence &	ps -C autossh
Invisible	xmessage hallo &	false
Schließen	:close
Beenden	:quit
```

