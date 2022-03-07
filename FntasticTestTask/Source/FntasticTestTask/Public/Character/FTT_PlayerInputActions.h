#pragma once

#include "CoreMinimal.h"






struct FPlayerInputActionNames
{

public:

	//................Moving................//

	const static FName MoveForwardAxis;
	const static FName MoveRightAxis;

	const static FName LookRightAxis;
	const static FName LookUpAxis;

	const static FName CrouchAction;
	const static FName SprintAction;
	const static FName WalkAction;

	const static FName JumpAction;

	//......................................//

	//..........Gameplay Actions............//

	const static FName InteractionAction;
	const static FName ParkurAction;

	const static FName CatchAction;

	//......................................//

	//...........Camera Actions.............//

	const static FName ChangeCameraDistanceAxis;

	const static FName SwitchTargetEnabledAction;
	const static FName ChangeTargetAction;

	//......................................//


	
};