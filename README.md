# What is this mod?
This modification, like other script hooks, adds a external scripting possibility to SA.
SA's SCM language has some major limitations -- so **NTAuthority** wrote this .NET scripting hook. 
It is inspired by HazardX's IV scripting hook, and based on the existing C++ SA script hook.

# How to use this mod?
Just copy the scripts directory and the .asi file to your SA directory. 
The .NET Framework 3.5, and the Visual C++ 2008 Runtime are required. 
For development its recommended using Visual Studio's IntelliSense feature, example scripts for C# are in the [scripts/dev](https://github.com/DurtyFree/GTA-SA-ScriptHook/tree/master/example/scripts/dev) directory.

The hook will read both compiled .dll files, and .cs/.vb files, though Visual Basic is untested. To open or close the console, just press `.

TestScript2.cs has a keybinding of 'U': spawn a Ballas member and add some health to the player.

RandomStuff.cs has more key bindings:
- 'I': display a text box
- 'O': Spawn a Vagos member.
- 'kill' in console: Kill the player.
- 'spawn groves' in console: spawn 3 GSF members around the player
