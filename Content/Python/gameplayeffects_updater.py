import os
from inspect import signature
from tkinter import Tk
from tkinter.filedialog import askdirectory, askopenfile
from pathlib import Path
import unreal
import csv

"""
 IDEA OF CREATING GAMEPLAY EFFECT ASSET AND POPULATING IT FROM PYTHON SCRIPT MAY NOT BE POSSIBLE
 AS ALMOST ALL THE PROPERTIES OF GameplayModifierInfo AND OTHER CLASSES ARE EDITSDEFAULTSONLY MEANING CANNOT
 BE EDITED ON AN INSTANCE. BUT I WILL COME BACK TO THIS ONCE PROJECT IS DONE.
"""

gameplay_effects_updater = None

def update_gameplayeffect():
    global gameplay_effects_updater
    if gameplay_effects_updater is not None:
        gameplay_effects_updater.update_player_gameplay_effect()
    else:
        unreal.log("the global instance is NOT present")

class GameplayEffectsUpdater:
    def __init__(self):
        global gameplay_effects_updater
        gameplay_effects_updater = self

    def create_menu_option(self, menus, tps_tool_menu):
        recreate_data_table = unreal.ToolMenuEntry(
            name="UpdatePlayerAttributesDefaultValues",
            owner=unreal.ToolMenuOwner(unreal.Name("LevelEditor.MainMenu.VSTools")),
            type=unreal.MultiBlockType.MENU_ENTRY,
        )
        recreate_data_table.set_label("Update Player's Attribute Set")
        recreate_data_table.set_tool_tip("Update player's attributes default values.")
        recreate_data_table.set_string_command(type=unreal.ToolMenuStringCommandType.PYTHON, custom_type="",
                                               string="import gameplayeffects_updater; gameplayeffects_updater.update_gameplayeffect()")

        tps_tool_menu.add_menu_entry(section_name="Update", args=recreate_data_table)
        menus.refresh_all_widgets()

    def update_player_gameplay_effect(self):
        # Ask for the directory that has all teh weapons' meshes.
        Tk().withdraw()
        content_dir_path = unreal.Paths.convert_relative_path_to_full(unreal.Paths.project_dir())
        file = askopenfile(mode='r', initialdir=content_dir_path, title="Select CSV with Player Attributes.",
                           filetypes=[("CSV Files",".csv")])
        csv_reader = csv.reader(file)

        # Hardcoding for now but this can also be asked form the user.
        ge_file_path = f"{unreal.Paths.project_content_dir()}Blueprints/AbilitySystem/GameplayEffects/AttributeDefaults"
        if not os.path.isdir(ge_file_path):
            os.makedirs(ge_file_path)

        ge_file_name = "GE_PlayerAttributes.uasset"

        full_path = os.path.join(ge_file_path, ge_file_name)

        # TODO - Delete the file if exists
        # if os.path.isfile(full_path):
        #     unreal.log(f"file {full_path} exists. Deleting it.")
        #     try:
        #         os.remove(full_path)
        #     except OSError:
        #         unreal.log("Error occurred while deleting ini files from Config/Tags")

        unreal.log("Creating the Gameplay effect file.")

        unreal.log(f"the file path is: {ge_file_path}")
        ge_file_path = ge_file_path.replace(unreal.Paths.project_content_dir(), "/Game/")
        unreal.log(f"the file path AFTER is: {ge_file_path}")
        ge_file = unreal.AssetToolsHelpers.get_asset_tools().create_asset(
            Path(ge_file_name).stem,
            ge_file_path,
            unreal.GameplayEffect,
            None
        )
        modifiers = unreal.Array(unreal.GameplayModifierInfo)
        # unreal.log(f"the type of ge file is:: {type(ge_file)}")
        # modifiers_list = ge_file.get_editor_property('modifiers')
        # modifier = unreal.GameplayModifierInfo()
        # modifiers_list.append(modifier)
        # ge_file.set_editor_property('modifiers', modifiers_list)

        unreal.log(f"the attribute is:: {unreal.GPAttributeBPFuncLib.get_player_attribute('MaxHealth')}")

        unreal.log(f"type of csv_reader:: {type(csv_reader)}")
        next(csv_reader)
        for row in csv_reader:
            attribute_name = row[0].split('.')[1] if '.' in row[0] else row[0]
            player_attribute = unreal.GPAttributeBPFuncLib.get_player_attribute(attribute_name)

            if player_attribute:
                unreal.log(f"Attribute with name {attribute_name} found")
                modifier = unreal.GameplayModifierInfo()

                (modifier.get_editor_property('attribute')).set_editor_property('attribute', player_attribute.get_editor_property('attribute'))

                unreal.log(modifier.get_editor_property('attribute').get_editor_property('attribute'))

                #modifier.set_editor_property('modifier_op', unreal.GameplayModOp.ADD_BASE)
                # (modifier.get_editor_property('modifier_op')).set_editor_property('modifier_op', unreal.GameplayModOp.ADD_BASE)
                #
                ((modifier.get_editor_property('modifier_magnitude')).get_editor_property('scalable_float_magnitude')).value=float(row[1])

                # (modifier.get_editor_property('attribute')).set_editor_property('attribute_name',
                #                                                                 player_attribute.get_editor_property(
                #                                                                     'attribute_name'))
                # (modifier.get_editor_property('attribute')).set_editor_property('attribute_owner',
                #                                                                 player_attribute.get_editor_property(
                #                                                                     'attribute_owner'))
                unreal.log(modifier.get_editor_property('attribute'))
            unreal.log('\n')
            break

        # directory = directory.replace(content_dir_path, "/Game/")
        #
        # # Load, Open and Read the csv file
        # with open(directory, mode='r') as file:
        #     csv_file = csv.reader(file)
        #     csv_headers = next(csv_file)
        #     unreal.log(f"csv_headers: {csv_headers}")
        #     # for header in csv_headers[1:]:
        #     #     unreal.log(f"CSV header {header} is not present in the datatable {temp_dt.get_name()}")
        #     #     break
