## OpenRA2 RV Rules Loader

A profile loader for [OpenRA2 Romanovs Vegeance](https://github.com/MustaphaTR/Romanovs-Vengeance). 

### The problem

The rules folder contains yaml files responsible for all of the game's logic allowing modifications with minimal difficulty. However, these yaml files must retain their original name. This presents the following difficulties:

- keep track of which version (original/modified) is currently in use
- quickly revert edits file causing game crash
- swap between different modes (Ex: Sandbox with overpowered units, Competitive with balanced units...)

### Fix paths

Unless you have the same exact folder setup I do, you will need to find and change the following code in `RA2VR_Loader.cpp`, (all located within `glueFunc` function):

#### Parent folders

```{c++}
const std::string RA_BASE = "BASE_PATH";
const std::string RA_MOD = "EDITS_PATH";
```

`BASE_PATH` = full path to OpenRA2 RV rules folder (Home + "OpenRA - Romanovs Vengeance.app/Contents/Resources/mods/rv/rules/")
`EDITS_PATH` = full path to yaml file edits folder

#### Source and target full paths

The following code chunk inside `glueFunc` function is to simplify and avoid repeating path strings.

```{c++}
const std::string AIR = "aircraft.yaml";
const std::string VEHICLE = "allied-vehicles.yaml";

//source
const std::filesystem::path SRC_PATHS[] = {
    RA_MOD+AIR, //air modified
    RA_MOD+"orig_rules/"+AIR, //air original
    RA_MOD+VEHICLE, //ground modified
    RA_MOD+"orig_rules/"+VEHICLE //ground original
};

//target
const std::filesystem::path TARGET_PATHS[] = {
    RA_BASE+AIR, //air
    RA_BASE+VEHICLE, //allied ground
};
```

The expected result should be 2 vectors of length 4 and 2 respectively.

For example:

`SRC_PATHS`[0] = `EDITS_PATH`+aircraft.yaml -> "Users/NAME/Desktop/RA2_Mods/aircraft.yaml"
`TARGET_PATHS`[0] = `BASE_PATH`+aircraft.yaml -> "/Users/NAME/Applications/OpenRA - Romanovs Vengeance.app/Contents/Resources/mods/rv/rules/aircraft.yaml"

### Next steps

Click [here]() to see features currently being worked on.
