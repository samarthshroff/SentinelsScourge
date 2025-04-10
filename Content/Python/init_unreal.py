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

if __name__=="__main__":
    create_tps_tool_menu()
    #table_creator = DataTablesCreator()
    #datatables_creator.data_table_creator.create_menu_option(menus, tps_tool_menu)
    #ge_updater = GameplayEffectsUpdater()
    #gameplayeffects_updater.gameplay_effects_updater.create_menu_option(menus, tps_tool_menu)
