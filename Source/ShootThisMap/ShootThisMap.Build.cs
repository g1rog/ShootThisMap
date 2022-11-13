
using UnrealBuildTool;

public class ShootThisMap : ModuleRules
{
	public ShootThisMap(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
		PrivateDependencyModuleNames.AddRange(new string[] {  });
		CppStandard = CppStandardVersion.Cpp20;
	}
}
