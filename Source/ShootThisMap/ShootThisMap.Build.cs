
using UnrealBuildTool;

public class ShootThisMap : ModuleRules
{
	public ShootThisMap(ReadOnlyTargetRules Target) : base(Target)
	{
		CppStandard = CppStandardVersion.Cpp20;
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
				"NavigationSystem"
			}
		);
	}
}
