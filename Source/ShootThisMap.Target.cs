

using UnrealBuildTool;
using System.Collections.Generic;

public class ShootThisMapTarget : TargetRules
{
	public ShootThisMapTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ShootThisMap" } );
	}
}
