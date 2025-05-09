import os
import shutil

import unreal
import sys

# # Needed when working on python scripts and reload is needed without the need to restart the ue project
# MODULE_NAME = "gameplayeffects_updater"
# if MODULE_NAME in sys.modules:
#     del sys.modules[MODULE_NAME]
# import gameplayeffects_updater
# from gameplayeffects_updater import GameplayEffectsUpdater

# Needed when working on python scripts and reload is needed without the need to restart the ue project
MODULE_NAME = "datatables_creator"
if MODULE_NAME in sys.modules:
    del sys.modules[MODULE_NAME]
import datatables_creator
from datatables_creator import DataTablesCreator

menus = None
tps_tool_menu = None

def create_tps_tool_menu():
    global menus
    menus = unreal.ToolMenus.get()
    main_menu = menus.find_menu(unreal.Name("LevelEditor.MainMenu"))

    menus.remove_menu(unreal.Name("LevelEditor.MainMenu.VSTools"))
    menus.remove_menu(unreal.Name("LevelEditor.MainMenu.MainMenu"))
    global tps_tool_menu
    tps_tool_menu = menus.find_menu(unreal.Name("LevelEditor.MainMenu.VSTools"))
    if tps_tool_menu is None:
        unreal.log("TpsTool menu NOT found. Creating One.")
        tps_tool_menu = main_menu.add_sub_menu(owner=unreal.Name("LevelEditor.MainMenu"), section_name="LevelEditor",
                                               name="VSTools", label="VSTools")
        menus.refresh_all_widgets()

def create_weapon_specific_attribute_set_classes():
    tags = []
    returned_tags = unreal.VSAbilitySystemLibrary.get_all_gameplay_tags_that_match('Weapon.Hero')
    for x in returned_tags:
        tag = unreal.StringLibrary.conv_name_to_string(unreal.Name.cast(x.get_editor_property("tag_name")))
        tag = tag.split('.')[-1]
        tags.append(tag)

    header_dir = f"{unreal.Paths.game_source_dir()}VampireSurvivorClone/Public/AbilitySystem/Generated/WeaponAttributeSets"
    print(header_dir)
    if not os.path.isdir(header_dir):
        #shutil.rmtree(header_dir)
        os.makedirs(header_dir)

    cpp_dir = f"{unreal.Paths.game_source_dir()}VampireSurvivorClone/Private/AbilitySystem/Generated/WeaponAttributeSets"
    print(cpp_dir)
    if not os.path.isdir(cpp_dir):
        #shutil.rmtree(cpp_dir)
        os.makedirs(cpp_dir)

    header_template = '''#pragma once
    #include "../../WeaponAttributeSet.h"
    #include "{weapon_name}AttributeSet.generated.h"

    UCLASS()
    class VAMPIRESURVIVORCLONE_API U{weapon_name}AttributeSet: public UWeaponAttributeSet
    {{
	    GENERATED_BODY()
    }};'''

    cpp_template = '''#include "AbilitySystem/Generated/WeaponAttributeSets/{weapon_name}AttributeSet.h"
    '''

    for weapon_name in tags:
        header_filename = os.path.join(header_dir,f"{weapon_name}AttributeSet.h")
        cpp_filename = os.path.join(cpp_dir, f"{weapon_name}AttributeSet.cpp")

        if os.path.exists(header_filename):
            print(f"File {weapon_name}AttributeSet.h exists. Continuing on with another tag, if any")
            continue

        with open(header_filename, "w") as header_file:
            header_file.write(header_template.format(weapon_name=weapon_name))

        with open(cpp_filename, "w") as cpp_file:
            cpp_file.write(cpp_template.format(weapon_name=weapon_name))

        print(f"Generated: {weapon_name}AttributeSet .h and .cpp")

def create_enemy_specific_attribute_set_classes():
    tags = []
    returned_tags = unreal.VSAbilitySystemLibrary.get_all_gameplay_tags_that_match('Enemy')
    for x in returned_tags:
        tag = unreal.StringLibrary.conv_name_to_string(unreal.Name.cast(x.get_editor_property("tag_name")))
        tag = tag.split('.')[-1]
        tags.append(tag)

    header_dir = f"{unreal.Paths.game_source_dir()}VampireSurvivorClone/Public/AbilitySystem/Generated/EnemiesAttributeSets"
    print(header_dir)
    if not os.path.isdir(header_dir):
        #shutil.rmtree(header_dir)
        os.makedirs(header_dir)

    cpp_dir = f"{unreal.Paths.game_source_dir()}VampireSurvivorClone/Private/AbilitySystem/Generated/EnemiesAttributeSets"
    print(cpp_dir)
    if not os.path.isdir(cpp_dir):
        #shutil.rmtree(cpp_dir)
        os.makedirs(cpp_dir)

    header_template = '''#pragma once
    #include "../../EnemyAttributeSet.h"
    #include "{enemy_name}AttributeSet.generated.h"

    UCLASS()
    class VAMPIRESURVIVORCLONE_API U{enemy_name}AttributeSet: public UEnemyAttributeSet
    {{
	    GENERATED_BODY()
    }};'''

    cpp_template = '''#include "AbilitySystem/Generated/EnemiesAttributeSets/{enemy_name}AttributeSet.h"
    '''

    for enemy_name in tags:
        header_filename = os.path.join(header_dir,f"{enemy_name}AttributeSet.h")
        cpp_filename = os.path.join(cpp_dir, f"{enemy_name}AttributeSet.cpp")

        if os.path.exists(header_filename):
            print(f"File {enemy_name}AttributeSet.h exists. Continuing on with another tag, if any")
            continue

        with open(header_filename, "w") as header_file:
            header_file.write(header_template.format(enemy_name=enemy_name))

        with open(cpp_filename, "w") as cpp_file:
            cpp_file.write(cpp_template.format(enemy_name=enemy_name))

        print(f"Generated: {enemy_name}AttributeSet .h and .cpp")

if __name__=="__main__":
    create_weapon_specific_attribute_set_classes()
    #create_enemy_specific_attribute_set_classes()

    #create_tps_tool_menu()
    #table_creator = DataTablesCreator()
    #datatables_creator.data_table_creator.create_menu_option(menus, tps_tool_menu)
    #ge_updater = GameplayEffectsUpdater()
    #gameplayeffects_updater.gameplay_effects_updater.create_menu_option(menus, tps_tool_menu)
