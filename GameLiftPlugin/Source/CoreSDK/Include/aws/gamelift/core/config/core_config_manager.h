// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.

#pragma once
// Standard Library

// AWS SDK
#include <aws/gamelift/core/logging.h>
#include <aws/core/utils/memory/AWSMemory.h>
#include <aws/core/utils/memory/stl/AWSMap.h>
#include <aws/core/utils/memory/stl/AWSList.h>
#include <aws/core/utils/memory/stl/AWSString.h>
#include <aws/core/config/AWSProfileConfigLoader.h>

namespace Aws {
    namespace Config
    {
        class ConfigAndCredentialsCacheManager;
    }
}

namespace GameLift
{
    namespace Config
    {
        class GAMELIFT_API GameLiftConfigManager
        {
        private:
            FuncLogCallback m_logCb = nullptr;

            Aws::Map<Aws::String, Aws::Config::Profile> m_profiles;

        protected:
            void SetProfiles(const Aws::Map<Aws::String, Aws::Config::Profile>& profiles);

        public:
            GameLiftConfigManager(FuncLogCallback logCallback, const Aws::Map<Aws::String, Aws::Config::Profile>& profiles);
            GameLiftConfigManager(FuncLogCallback logCallback);
            virtual ~GameLiftConfigManager();

            Aws::List<Aws::String> GetProfileNames();

            bool CreateProfile(const Aws::String& profileName);
            bool RenameProfile(const Aws::String& profileName, const Aws::String& newProfileName);

            const Aws::String& GetAccessKey(const Aws::String& profileName) const;
            bool SetAccessKey(const Aws::String& profileName, const Aws::String& accessKey);
            const Aws::String& GetSecretAccessKey(const Aws::String& profileName) const;
            bool SetSecretAccessKey(const Aws::String& profileName, const Aws::String& secretAccessKey);
            const Aws::String& GetSessionToken(const Aws::String& profileName) const;
            bool SetSessionToken(const Aws::String& profileName, const Aws::String& accessToken);
            const Aws::String& GetRegion(const Aws::String& profileName) const;
            bool SetRegion(const Aws::String& profileName, const Aws::String& region);

            bool Save();

        private:
            bool Exist(const Aws::String& profileName) const;
        };
    }
}
