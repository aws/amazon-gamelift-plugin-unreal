// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "Converter.h"
#include "aws/gamelift/core/errors.h"
#include "Containers/Map.h"

namespace Internal
{
	TMap<unsigned int, FString> InitMap()
	{
		return TMap<unsigned int, FString>(
		{
			// Standard status codes (0-500)
			{ GameLift::GAMELIFT_SUCCESS, "SUCCESS" },
			{ GameLift::GAMELIFT_ERROR_INVALID_PROVIDER, "INVALID PROVIDER" },
			{ GameLift::GAMELIFT_ERROR_PARAMETERS_FILE_SAVE_FAILED, "PARAMETERS FILE SAVE FAILED" },
			{ GameLift::GAMELIFT_ERROR_CLOUDFORMATION_FILE_SAVE_FAILED, "CLOUDFORMATION FILE SAVE FAILED" },
			{ GameLift::GAMELIFT_ERROR_FUNCTIONS_COPY_FAILED, "FUNCTIONS COPY FAILED" },
			{ GameLift::GAMELIFT_ERROR_SETTINGS_FILE_SAVE_FAILED, "SETTINGS FILE SAVE FAILED" },
			{ GameLift::GAMELIFT_ERROR_NO_ID_TOKEN, "NO ID TOKEN" },
			{ GameLift::GAMELIFT_ERROR_HTTP_REQUEST_FAILED, "HTTP REQUEST FAILED" },
			{ GameLift::GAMELIFT_ERROR_PARSE_JSON_FAILED, "PARSE JSON FAILED" },
			{ GameLift::GAMELIFT_ERROR_SIGN_REQUEST_FAILED, "SIGN REQUEST FAILED" },
			{ GameLift::GAMELIFT_ERROR_SETTINGS_FILE_READ_FAILED, "SETTINGS FILE READ FAILED" },
			{ GameLift::GAMELIFT_ERROR_FILE_OPEN_FAILED, "FILE OPEN FAILED" },
			{ GameLift::GAMELIFT_ERROR_FILE_WRITE_FAILED, "FILE WRITE FAILED" },
			{ GameLift::GAMELIFT_ERROR_FILE_READ_FAILED, "FILE READ FAILED" },
			{ GameLift::GAMELIFT_ERROR_DIRECTORY_CREATE_FAILED, "DIRECTORY CREATE FAILED" },
			{ GameLift::GAMELIFT_ERROR_DIRECTORY_NOT_FOUND, "DIRECTORY NOT FOUND" },
			{ GameLift::GAMELIFT_ERROR_METHOD_NOT_IMPLEMENTED, "METHOD NOT IMPLEMENTED" },
			{ GameLift::GAMELIFT_ERROR_GENERAL, "GAMELIFT ERROR GENERAL" },
			{ GameLift::GAMELIFT_ERROR_REGION_CODE_CONVERSION_FAILED, "REGION CODE CONVERSION FAILED" },

			// Bootstrapping status codes (501-1000)
			{ GameLift::GAMELIFT_ERROR_BOOTSTRAP_BUCKET_LOOKUP_FAILED, "BOOTSTRAP BUCKET LOOKUP FAILED" },
			{ GameLift::GAMELIFT_ERROR_BOOTSTRAP_BUCKET_CREATION_FAILED, "BOOTSTRAP BUCKET CREATION FAILED" },
			{ GameLift::GAMELIFT_ERROR_BOOTSTRAP_INVALID_REGION_CODE, "BOOTSTRAP INVALID REGION CODE" },
			{ GameLift::GAMELIFT_ERROR_BOOTSTRAP_MISSING_PLUGIN_ROOT, "BOOTSTRAP MISSING PLUGIN ROOT" },
			{ GameLift::GAMELIFT_ERROR_BOOTSTRAP_REGION_CODE_CONVERSION_FAILED, "BOOTSTRAP REGION CODE CONVERSION FAILED" },

			// Resource creation status codes (1001-1500)
			{ GameLift::GAMELIFT_ERROR_FUNCTIONS_PATH_NOT_FOUND, "FUNCTIONS PATH NOT FOUND" },
			{ GameLift::GAMELIFT_ERROR_CLOUDFORMATION_PATH_NOT_FOUND, "CLOUDFORMATION PATH NOT FOUND" },
			{ GameLift::GAMELIFT_ERROR_FUNCTION_ZIP_INIT_FAILED, "FUNCTION ZIP INIT FAILED" },
			{ GameLift::GAMELIFT_ERROR_FUNCTION_ZIP_WRITE_FAILED, "FUNCTION ZIP WRITE FAILED" },
			{ GameLift::GAMELIFT_ERROR_PARAMSTORE_WRITE_FAILED, "PARAMSTORE WRITE FAILED" },
			{ GameLift::GAMELIFT_ERROR_BOOTSTRAP_BUCKET_UPLOAD_FAILED, "BOOTSTRAP BUCKET UPLOAD FAILED" },
			{ GameLift::GAMELIFT_ERROR_SECRETSMANAGER_WRITE_FAILED, "SECRETSMANAGER WRITE FAILED"},
			{ GameLift::GAMELIFT_ERROR_CLOUDFORMATION_STACK_CREATION_FAILED, "CLOUDFORMATION STACK CREATION FAILED" },
			{ GameLift::GAMELIFT_ERROR_CLOUDFORMATION_STACK_UPDATE_FAILED, "CLOUDFORMATION_STACK_CREATION FAILED" },
			{ GameLift::GAMELIFT_ERROR_CLOUDFORMATION_RESOURCE_CREATION_FAILED, "CLOUDFORMATION RESOURCE CREATION_FAILED" },
			{ GameLift::GAMELIFT_ERROR_CLOUDFORMATION_STACK_DELETE_FAILED, "CLOUDFORMATION STACK DELETE FAILED" },
			{ GameLift::GAMELIFT_ERROR_CLOUDFORMATION_DESCRIBE_RESOURCE_FAILED, "CLOUDFORMATION DESCRIBE RESOURCE FAILED" },
			{ GameLift::GAMELIFT_ERROR_CLOUDFORMATION_DESCRIBE_STACKS_FAILED, "CLOUDFORMATION DESCRIBE STACKS FAILED" },
			{ GameLift::GAMELIFT_ERROR_APIGATEWAY_DEPLOYMENT_CREATION_FAILED, "APIGATEWAY DEPLOYMENT CREATION FAILED" },
			{ GameLift::GAMELIFT_ERROR_APIGATEWAY_STAGE_DEPLOYMENT_FAILED, "APIGATEWAY STAGE DEPLOYMENT FAILED" },
			{ GameLift::GAMELIFT_ERROR_LAYERS_PATH_NOT_FOUND, "LAYERS PATH NOT FOUND" },
			{ GameLift::GAMELIFT_ERROR_LAYER_ZIP_INIT_FAILED, "LAYER ZIP INIT FAILED" },
			{ GameLift::GAMELIFT_ERROR_LAYER_ZIP_WRITE_FAILED, "LAYER ZIP WRITE FAILED" },
			{ GameLift::GAMELIFT_ERROR_LAYER_CREATION_FAILED, "LAYER CREATION FAILED" },
			{ GameLift::GAMELIFT_ERROR_CLOUDFORMATION_GET_TEMPLATE_FAILED, "CLOUDFORMATION GET TEMPLATE FAILED" },
			{ GameLift::GAMELIFT_ERROR_PARAMSTORE_READ_FAILED, "PARAMSTORE READ FAILED" },
			{ GameLift::GAMELIFT_ERROR_GAME_SERVER_PATH_NOT_FOUND, "GAME SERVER PATH NOT FOUND" },
			{ GameLift::GAMELIFT_ERROR_GAME_SERVER_ZIP_INIT_FAILED, "GAME SERVER ZIP INIT FAILED" },
			{ GameLift::GAMELIFT_ERROR_GAME_SERVER_ZIP_WRITE_FAILED, "GAME SERVER ZIP WRITE FAILED" },
			{ GameLift::GAMELIFT_ERROR_GAME_SERVER_ZIP_READ_FAILED, "GAME SERVER ZIP READ FAILED" },

			// Identity status codes (0x10000 - 0x103FF)
			{ GameLift::GAMELIFT_ERROR_REGISTER_USER_FAILED, "REGISTER USER FAILED" },
			{ GameLift::GAMELIFT_ERROR_CONFIRM_REGISTRATION_FAILED, "CONFIRM REGISTRATION FAILED"  },
			{ GameLift::GAMELIFT_ERROR_RESEND_CONFIRMATION_CODE_FAILED, "RESEND CONFIRMATION CODE FAILED" },
			{ GameLift::GAMELIFT_ERROR_LOGIN_FAILED, "LOGIN FAILED" },
			{ GameLift::GAMELIFT_ERROR_FORGOT_PASSWORD_FAILED, "FORGOT PASSWORD FAILED" },
			{ GameLift::GAMELIFT_ERROR_CONFIRM_FORGOT_PASSWORD_FAILED, "CONFIRM FORGOT PASSWORD FAILED" },
			{ GameLift::GAMELIFT_ERROR_GET_USER_FAILED, "GET USER FAILED" },
			{ GameLift::GAMELIFT_ERROR_LOGOUT_FAILED, "LOGOUT FAILED" },
			{ GameLift::GAMELIFT_ERROR_MALFORMED_USERNAME, "MALFORMED USERNAME" },
			{ GameLift::GAMELIFT_ERROR_MALFORMED_PASSWORD, "MALFORMED PASSWORD" },
			{ GameLift::GAMELIFT_ERROR_INVALID_FEDERATED_IDENTITY_PROVIDER, "INVALID FEDERATED IDENTITY PROVIDER" },

			// Achievements status codes (0x10800 - 0x10BFF)
			{ GameLift::GAMELIFT_ERROR_ACHIEVEMENTS_ICON_UPLOAD_FAILED, "ACHIEVEMENTS ICON UPLOAD FAILED"},
			{ GameLift::GAMELIFT_ERROR_ACHIEVEMENTS_INVALID_ID, "ACHIEVEMENTS INVALID ID" },

			// User Gameplay Data status codes (0x10C00 - 0x10FFF)
			{ GameLift::GAMELIFT_ERROR_USER_GAMEPLAY_DATA_PAYLOAD_INVALID, "USER GAMEPLAY DATA PAYLOAD INVALID"},
			{ GameLift::GAMELIFT_ERROR_USER_GAMEPLAY_DATA_API_CALL_FAILED, "USER GAMEPLAY DATA API CALL FAILED"},
			{ GameLift::GAMELIFT_ERROR_USER_GAMEPLAY_DATA_API_CALL_DROPPED, "USER GAMEPLAY DATA API CALL DROPPED"},
			{ GameLift::GAMELIFT_WARNING_USER_GAMEPLAY_DATA_API_CALL_ENQUEUED, "GAMELIFT WARNING USER GAMEPLAY DATA API CALL ENQUEUED"},
			{ GameLift::GAMELIFT_ERROR_MALFORMED_BUNDLE_NAME, "MALFORMED BUNDLE NAME"},
			{ GameLift::GAMELIFT_ERROR_MALFORMED_BUNDLE_ITEM_KEY, "MALFORMED BUNDLE ITEM KEY"},
			{ GameLift::GAMELIFT_ERROR_USER_GAMEPLAY_DATA_CACHE_WRITE_FAILED, "USER GAMEPLAY DATA CACHE WRITE FAILED"},
			{ GameLift::GAMELIFT_ERROR_USER_GAMEPLAY_DATA_CACHE_READ_FAILED, "USER GAMEPLAY DATA CACHE READ FAILED"},

			// Game Saving status codes (0x11000 - 0x113FF)
			{ GameLift::GAMELIFT_ERROR_GAME_SAVING_SLOT_NOT_FOUND, "GAME SAVING SLOT NOT FOUND" },
			{ GameLift::GAMELIFT_ERROR_GAME_SAVING_CLOUD_SLOT_IS_NEWER, "GAME SAVING CLOUD SLOT IS NEWER" },
			{ GameLift::GAMELIFT_ERROR_GAME_SAVING_SYNC_CONFLICT, "GAME SAVING SYNC CONFLICT" },
			{ GameLift::GAMELIFT_ERROR_GAME_SAVING_DOWNLOAD_SLOT_ALREADY_IN_SYNC, "GAME SAVING DOWNLOAD SLOT ALREADY IN SYNC" },
			{ GameLift::GAMELIFT_ERROR_GAME_SAVING_UPLOAD_SLOT_ALREADY_IN_SYNC, "GAME SAVING UPLOAD SLOT ALREADY IN SYNC" },
			{ GameLift::GAMELIFT_ERROR_GAME_SAVING_EXCEEDED_MAX_SIZE, "GAME SAVING EXCEEDED MAX SIZE" },
			{ GameLift::GAMELIFT_ERROR_GAME_SAVING_FILE_EMPTY, "GAME SAVING FILE EMPTY" },
			{ GameLift::GAMELIFT_ERROR_GAME_SAVING_FILE_FAILED_TO_OPEN, "GAME SAVING FILE FAILED TO OPEN" },
			{ GameLift::GAMELIFT_ERROR_GAME_SAVING_LOCAL_SLOT_IS_NEWER, "GAME SAVING LOCAL SLOT IS NEWER" },
			{ GameLift::GAMELIFT_ERROR_GAME_SAVING_SLOT_UNKNOWN_SYNC_STATUS, "GAME SAVING SLOT UNKNOWN SYNC STATUS" },
			{ GameLift::GAMELIFT_ERROR_GAME_SAVING_MALFORMED_SLOT_NAME, "GAME SAVING MALFORMED SLOT_NAME" },
			{ GameLift::GAMELIFT_ERROR_GAME_SAVING_MISSING_SHA, "GAME SAVING MISSING SHA" },
			{ GameLift::GAMELIFT_ERROR_GAME_SAVING_SLOT_TAMPERED, "GAME SAVING SLOT TAMPERED" },
			{ GameLift::GAMELIFT_ERROR_GAME_SAVING_BUFFER_TOO_SMALL, "GAME SAVING BUFFER TOO SMALL" },
			{ GameLift::GAMELIFT_ERROR_GAME_SAVING_MAX_CLOUD_SLOTS_EXCEEDED, "GAME SAVING MAX CLOUD SLOTSEXCEEDED" }
		}); 
	}
} // namespace Internal

namespace GameLiftErrorAsString
{
	FString Convert(unsigned int ErrorCode)
	{
		static auto ErrorCodeMap = Internal::InitMap();

		if (ErrorCodeMap.Contains(ErrorCode))
		{
			return ErrorCodeMap[ErrorCode];
		}

		return FString("GAMELIFT ERROR GENERAL");
	}
} // namespace GameLiftErrorAsString
