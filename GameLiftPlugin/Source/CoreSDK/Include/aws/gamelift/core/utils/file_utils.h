// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.

#pragma once

// Standard Library
#include <fstream>
#include <sstream>

// AWS SDK
#include <aws/core/utils/base64/Base64.h>

// GameLift
#include <aws/gamelift/core/api.h>
#include <aws/gamelift/core/awsclients/default_clients.h>
#include <aws/gamelift/core/errors.h>
#include <aws/gamelift/core/logging.h>

// Forward declaration
namespace YAML { class Node; }

namespace GameLift
{
    namespace Utils
    {
        class GAMELIFT_API FileUtils
        {
        private:
            /**
             * @brief Returns an open handler to the specified file. Creates the file if it doesn't exist. Creates missing directories in the filePath.
             *
             * @param filePath The absolute or relative path plus the filename of the file to write (UTF-8 encoded). Example: "foo.json", "..\\foo.json", or "C:\\Program Files\\foo.json".
             * @param returnFileStream (Out Parameter) An open stream to the specified file.
             * @param logCallback (Optional) If provided and the write fails, will log a human readable error message.
             * @param errorMessagePrefix (Optional) A prefix to put in front of the error message. Example: "GameSaving::DownloadCloudSlot() ".
             * @return GAMELIFT_SUCCESS if the file was successfully opened, otherwise returns GAMELIFT_ERROR_FILE_OPEN_FAILED or GAMELIFT_ERROR_DIRECTORY_CREATE_FAILED.
             */
            static unsigned int createOrOpenFile(const std::string& filePath, std::ofstream& returnFileStream, FuncLogCallback logCallback = nullptr, const std::string& errorMessagePrefix = "");

        public:
            /**
            * @brief Calculates the hash of an entire directory.
            *
            * @param directoryPath The absolute or relative path of the directory to hash (UTF-8 encoded). Example: "foo", "..\\foo", or "C:\\Program Files\\foo".
            * @param returnedString (Out Parameter) The string to write into. If the operation fails, the string will be empty: "".
            * @param logCallback (Optional) If provided and the operation fails, will log a human readable error message.
            * @return GAMELIFT_SUCCESS if the directory hash was successfully calculated and the return string written to, otherwise returns GAMELIFT_ERROR_DIRECTORY_NOT_FOUND.
            */
            static unsigned int CalculateDirectoryHash(const std::string& directoryPath, std::string& returnedString, FuncLogCallback logCallback = nullptr);

            /**
             * @brief Load a file into a string.
             *
             * @param filePath The absolute or relative path plus the filename of the file to read (UTF-8 encoded). Example: "foo.json", "..\\foo.json", or "C:\\Program Files\\foo.json".
             * @param returnedString (Out Parameter) The string to write into. If the operation fails, the string will be empty: "".
             * @param logCallback (Optional) If provided and the operation fails, will log a human readable error message.
             * @param errorMessagePrefix (Optional) A prefix to put in front of the error message. Example: "GameSaving::LoadMetadata() ".
             * @return GAMELIFT_SUCCESS if the file was successfully read from and the string written to, otherwise returns GAMELIFT_ERROR_FILE_OPEN_FAILED or GAMELIFT_ERROR_FILE_READ_FAILED.
             */
            static unsigned int ReadFileIntoString(const std::string& filePath, std::string& returnedString, FuncLogCallback logCallback = nullptr, const std::string& errorMessagePrefix = "");

            /**
             * @brief Write a string to a file. Overwrites the file if it already exists, otherwise creates a new file. Creates missing directories in the filePath.
             *
             * @param sourceString The string to write to the file.
             * @param filePath The absolute or relative path plus the filename of the file to write (UTF-8 encoded). Example: "foo.json", "..\\foo.json", or "C:\\Program Files\\foo.json".
             * @param logCallback (Optional) If provided and the write fails, will log a human readable error message.
             * @param errorMessagePrefix (Optional) A prefix to put in front of the error message. Example: "GameSaving::SaveMetadata() ".
             * @return GAMELIFT_SUCCESS if the file was successfully written to, otherwise returns GAMELIFT_ERROR_FILE_OPEN_FAILED, GAMELIFT_ERROR_FILE_WRITE_FAILED, or GAMELIFT_ERROR_DIRECTORY_CREATE_FAILED.
             */
            static unsigned int WriteStringToFile(const std::string& sourceString, const std::string& filePath, FuncLogCallback logCallback = nullptr, const std::string& errorMessagePrefix = "");

            /**
             * @brief Writes the contents of a stream to a file. Overwrites the file if it already exists, otherwise creates a new file. Creates missing directories in the filePath.
             *
             * @param sourceStream The stream to write to the file.
             * @param filePath The absolute or relative path plus the filename of the file to write (UTF-8 encoded). Example: "foo.json", "..\\foo.json", or "C:\\Program Files\\foo.json".
             * @param logCallback (Optional) If provided and the write fails, will log a human readable error message.
             * @param errorMessagePrefix (Optional) A prefix to put in front of the error message. Example: "GameSaving::DownloadCloudSlot() ".
             * @return GAMELIFT_SUCCESS if the file was successfully written to, otherwise returns GAMELIFT_ERROR_FILE_OPEN_FAILED, GAMELIFT_ERROR_FILE_WRITE_FAILED, or GAMELIFT_ERROR_DIRECTORY_CREATE_FAILED.
             */
            static unsigned int WriteStreamToFile(const std::istream& sourceStream, const std::string& filePath, FuncLogCallback logCallback = nullptr, const std::string& errorMessagePrefix = "");

            /**
             * @brief Loads and parses an existing YAML file.
             *
             * @param filePath The absolute or relative path plus the filename of the file to write (UTF-8 encoded). Example: "foo.json", "..\\foo.json", or "C:\\Program Files\\foo.json".
             * @param returnedNode Reference to `YAML::Node` variable that will be assigned the root node if load is successful.
             * @param logCallback (Optional) If provided and the operation fails, will log a human readable error message.
             * @param errorMessagePrefix (Optional) A prefix to put in front of the error message. Example: "GameSaving::DownloadCloudSlot() ".
             * @return GAMELIFT_SUCCESS if the file was successfully written to, otherwise returns GAMELIFT_ERROR_FILE_OPEN_FAILED, GAMELIFT_ERROR_FILE_WRITE_FAILED, or GAMELIFT_ERROR_DIRECTORY_CREATE_FAILED.
             */
            static unsigned int ReadFileAsYAML(const std::string& filePath, YAML::Node& returnedNode, FuncLogCallback logCallback = nullptr, const std::string& errorMessagePrefix = "");

            /**
             * @brief Writes a YAML document to a file. Overwrites the file if it already exists, otherwise creates a new file. Creates missing directories in the filePath.
             *
             * @param node The root node of the YAML document to be written to disk.
             * @param filePath The absolute or relative path plus the filename of the file to write (UTF-8 encoded). Example: "foo.json", "..\\foo.json", or "C:\\Program Files\\foo.json".
             * @param headerComment (Optional) Header string that is written before the serialized YAML, should be formatted as a YAML comment.
             * @param logCallback (Optional) If provided and the write fails, will log a human readable error message.
             * @param errorMessagePrefix (Optional) A prefix to put in front of the error message. Example: "GameSaving::DownloadCloudSlot() ".
             * @return GAMELIFT_SUCCESS if the file was successfully written to, otherwise returns GAMELIFT_ERROR_FILE_OPEN_FAILED, GAMELIFT_ERROR_FILE_WRITE_FAILED, or GAMELIFT_ERROR_DIRECTORY_CREATE_FAILED.
             */
            static unsigned int WriteYAMLToFile(const YAML::Node& rootNode, const std::string& filePath, const std::string& headerComment = "", FuncLogCallback logCallback = nullptr, const std::string & errorMessagePrefix = "");

#if _WIN32
            typedef std::wstring PlatformPathString;
#else
            typedef std::string PlatformPathString;
#endif
            /**
             * @brief Converts UTF-8 path strings for use with platform-native file APIs
             *
             * @param pathString The UTF-8 encoded string to be converted
             * @return The converted wstring (Windows) or a copy of the source string (other platforms)
             */
            static PlatformPathString PathFromUtf8(const std::string& pathString);

            /**
             * @brief Converts platform-native path strings to UTF-8 for use with GameLift
             *
             * @param pathString A UTF-16 wide string (Windows), or a UTF-8 string (other platforms)
             * @return The converted UTF-8 string (Windows) or a copy of the source string (other platforms)
             */
            static std::string PathToUtf8(const PlatformPathString& pathString);

            /**
             * @brief Checks if the file exists
             *
             * @param pathString The absolute or relative path plus the filename of the file to check for existance (UTF-8 encoded)
             * @return True if the file exists, False - otherwise
             */
            static bool FileExists(const std::string& filePath);
        };
    }
}
