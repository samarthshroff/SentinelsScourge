import os
import tkinter
from pathlib import Path
from tkinter import Tk
from tkinter.filedialog import askdirectory

import unreal

data_table_creator = None
initiated_from_tool_menu = False

def create_tables():
    global data_table_creator
    if data_table_creator is not None:
        global initiated_from_tool_menu
        initiated_from_tool_menu = True
        data_table_creator.create_tables()
    else:
        unreal.log("the global instance is NOT present")

class DataTablesCreator:
    directory : str = None
    asset_tools : unreal.AssetTools = None
    data_table_factory : unreal.DataTableFactory = None
    csv_path : str = None

    def __init__(self):
        global data_table_creator
        data_table_creator = self
        self.create_tables()

    def create_menu_option(self, menus, tps_tool_menu):
            recreate_data_table = unreal.ToolMenuEntry(
                name="RecreateDataTables",
                owner=unreal.ToolMenuOwner(unreal.Name("LevelEditor.MainMenu.VSTools")),
                type=unreal.MultiBlockType.MENU_ENTRY,
            )
            recreate_data_table.set_label("Recreate DataTable(s)")
            recreate_data_table.set_string_command(type=unreal.ToolMenuStringCommandType.PYTHON,custom_type="", string="import datatables_creator; datatables_creator.create_tables()")

            tps_tool_menu.add_menu_entry(section_name="Update",args=recreate_data_table)
            menus.refresh_all_widgets()

    def create_tables(self):
        self.csv_path = f"{unreal.Paths.project_dir()}DataTablesCSVs"
        # Get asset tool Helpers
        self.asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
        self.data_table_factory = unreal.DataTableFactory()
        self.delete_all_existing_data_tables()
        self.create_all_weapons_table()
        var = tkinter.messagebox.showinfo("DataTables Updated!", f"Datatable(s) location is: {unreal.Paths.project_content_dir()}/DataTables")

    def delete_all_existing_data_tables(self):
        self.directory = "/Game/DataTables"
        if unreal.EditorAssetLibrary.does_directory_exist(self.directory):
            unreal.EditorAssetLibrary.delete_directory (self.directory)
        unreal.EditorAssetLibrary.make_directory(self.directory)

    def create_all_weapons_table(self):
        unreal.log(f"csv path is {self.csv_path}")
        file_names = os.listdir(self.csv_path)
        unreal.log(file_names)

        row_struct = unreal.find_object(None, "/Script/VampireSurvivorClone.EnemyMetaData")
        if not row_struct:
            unreal.log_error("Row structure data FWeaponMetaData not found")
            raise Exception("Row structure data not found")
        unreal.log(f"directory:: {self.directory}")
        self.data_table_factory.set_editor_property("struct", row_struct)

        for file_name in file_names:
            new_datatable = self.asset_tools.create_asset(f"DT_{Path(file_name).stem}", self.directory, unreal.DataTable, self.data_table_factory)

            if new_datatable is not None:
                new_datatable.set_editor_property("ignore_missing_fields", True)
                new_datatable.fill_from_csv_file(f"{self.csv_path}/{file_name}")




