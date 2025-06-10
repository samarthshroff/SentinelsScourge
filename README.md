# Sentinel's Scourge – Technical Release Notes

Sentinel's Scourge is a feature-rich Unreal Engine project demonstrating advanced gameplay systems, procedural content generation, and robust code 
architecture. The project leverages a variety of powerful Unreal Engine features and programming best practices to deliver scalable, dynamic, and polished gameplay experiences.

## Key Unreal Engine Features

- **Gameplay Ability System Integration**
  - Deep integration with Unreal’s Gameplay Ability System (GAS) for highly modular, extensible character abilities and effects.
  - Custom BlueprintFunctionLibrary (SSAbilitySystemLibrary) for querying and manipulating gameplay tags and attributes at runtime and via Python scripting.

- **Dynamic Attribute Management**
  - Automated generation of AttributeSet C++ classes for both weapons ~~and enemies~~ using custom Python scripts, based on gameplay tags.
  - Supports rapid extension and maintenance of new weapons ~~/enemies~~ with unique stats, reducing boilerplate and human error.

- **Data-Driven Gameplay Effects**
  - Tools for importing and updating gameplay effects (e.g., player attributes) from external CSV files, streamlining balancing and iteration.
  - Attribute and effect data stored and updated as Unreal assets programmatically.

- **Advanced AI with Behavior Trees**
  - Enemy AI utilizes Unreal’s Behavior Tree system, with custom AEnemyAIController classes, blackboards, and perception components for sophisticated decision-making.
  - Enemy spawner and data asset system for efficient, asynchronous loading of skeletal meshes, animation blueprints, and montage assets for diverse enemy types.

- **Weapon and Combat Architecture**
  - Modular weapon system using UWeaponData data assets, supporting a rich taxonomy of weapon categories and behaviors (e.g., projectile, melee, unique, transformative).
  - Gameplay tags and effect replication tailored for both PvE and PvP scenarios.

- **Efficient Asset Management**
  - Asynchronous asset streaming for meshes, animations, and effects to optimize performance and minimize loading hitches during gameplay.
  - Delegates and soft object pointers ensure assets are loaded and initialized on-demand.

## Advanced Programming Techniques

- **Python Scripting for Editor Automation**
  - In-editor Python scripts automate repetitive Unreal Engine C++/Blueprint tasks, such as generating new AttributeSet classes. The system is designed for future expansion to update gameplay effect assets automatically, though this feature is currently under development due to Unreal Engine’s editor scripting limitations.
  - Enables rapid prototyping and batch operations without recompiling or restarting the Unreal Editor.

- **C++ Polymorphism and Interface Design**
  - Extensive use of interfaces (e.g., ISSGameplayAbilityInterface) for ability contract enforcement and component-based architecture.
  - TSubclassOf, TObjectPtr, and UDataAsset patterns used throughout for safe, extensible asset referencing.

- **Robust Modularization**
  - Clear separation of concerns between character, weapon, enemy, and ability logic.
  - Public/private headers and generated code directories used for organization and scalability.

- **Blueprint/C++ Hybrid Approach**
  - Exposes key systems and data to Blueprints for designer extensibility while keeping core logic in performant C++ modules.

## Notable Systems and Components

- **HeroAbilitySystemComponent & WeaponManager**
  - Handles ability cooldowns, weapon initialization, and effect application, enabling complex player progression and customization.

- **EnemyData & EnemySpawner**
  - Data-driven enemy spawning and initialization, supporting procedural encounters and scalable content addition.

- **Custom Gameplay Tags**
  - Rich taxonomy of gameplay tags for weapon categories, cooldowns, and effect types, facilitating highly modular gameplay logic.

## License and Usage

This project is licensed under the [Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International (CC BY-NC-ND 4.0)](https://creativecommons.org/licenses/by-nc-nd/4.0/).
[![License: CC BY-NC-ND 4.0](https://licensebuttons.net/l/by-nc-nd/4.0/88x31.png)](http://creativecommons.org/licenses/by-nc-nd/4.0/)

### What does this mean?
- **Personal/Non-Commercial Use:**  
  You are free to view, download, and share this project for personal and non-commercial purposes, as long as you provide appropriate credit to the author.

- **No Derivatives:**  
  You may not modify, remix, or create derivative works based on this project. Pull requests and contributions are not accepted.

- **Commercial Use:**  
  Commercial use of this project, in whole or in part, is not permitted without explicit written permission from the author. If you wish to use this project
  commercially, please contact [samarthshroff](mailto:samarth.shroff@gmail.com) to discuss licensing and attribution requirements.

### Unreal Engine Content Notice
This project may include content (code, binaries, or assets) provided by Epic Games, Inc. (“Epic”) under the Unreal Engine End User License Agreement (EULA).  
Such content is subject to the [Unreal Engine EULA](https://www.unrealengine.com/eula) and may not be redistributed except as permitted by that agreement.

### Summary Table

| Use Case           | Allowed? | Notes                                                                 |
|--------------------|----------|-----------------------------------------------------------------------|
| Personal/Portfolio | ✅       | Credit required                                                      |
| Non-Commercial     | ✅       | Credit required                                                      |
| Commercial         | ❌       | Contact author for permission and credit requirements                 |
| Modification       | ❌       | No derivatives; do not submit pull requests or modified versions      |

For more details, see the [LICENSE](LICENSE.md) file in this repository.
