
using UnrealBuildTool;

public class ShootThisMap : ModuleRules
{
	public ShootThisMap(ReadOnlyTargetRules Target) : base(Target)
	{
		CppStandard = CppStandardVersion.Latest;
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange
		(new string[] 
			{   "Core", 
				"CoreUObject", 
				"Engine", 
				"InputCore", 
				"Niagara", 
				"PhysicsCore",
				"GameplayTasks",
				"NavigationSystem",
			}
		);
		PublicIncludePaths.AddRange(new string[]
		{
			"ShootThisMap/Public/Player",
			"ShootThisMap/Public/Components",
			"ShootThisMap/Public/Dev",
			"ShootThisMap/Public/Weapon",
			"ShootThisMap/Public/UI",
			"ShootThisMap/Public/Animations",
			"ShootThisMap/Public/Pickups",
			"ShootThisMap/Public/Weapon/Components",
			"ShootThisMap/Public/AI",
			"ShootThisMap/Public/AI/Tasks",
			"ShootThisMap/Public/AI/Services",
			"ShootThisMap/Public/AI/EQS",
			"ShootThisMap/Public/AI/Decorators",
			"ShootThisMap/Public/Menu",
			"ShootThisMap/Public/Menu/UI",
			"ShootThisMap/Public/Sound",
		});
	}
}
