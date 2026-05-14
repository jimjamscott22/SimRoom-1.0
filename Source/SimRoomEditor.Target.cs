using UnrealBuildTool;
using System.Collections.Generic;

public class SimRoomEditorTarget : TargetRules
{
	public SimRoomEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("SimRoom");
	}
}
