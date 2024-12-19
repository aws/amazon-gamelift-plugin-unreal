$ErrorActionPreference="Stop"
echo "Running aws ecr get-login-password --region {{REGION}} --profile {{PROFILE_NAME}} | docker login --username AWS --password-stdin {{ECR_REGISTRY_URL}}"
aws ecr get-login-password --region {{REGION}} --profile {{PROFILE_NAME}} | docker login --username AWS --password-stdin {{ECR_REGISTRY_URL}}
if (!$LastExitCode -eq 0) {
  echo "Docker login has failed."
  exit $LastExitCode
}
echo "Running docker build -t {{REPO_NAME}}:{{IMAGE_TAG}} {{IMAGE_PATH}}"
docker build -t {{REPO_NAME}}:{{IMAGE_TAG}} "{{IMAGE_PATH}}" --progress=plain --build-arg GAME_BUILD_DIRECTORY={{GAME_BUILD_DIRECTORY}} --build-arg GAME_EXECUTABLE={{GAME_EXECUTABLE}}
if (!$LastExitCode -eq 0) {
  echo "Docker build has failed."
  exit $LastExitCode
}
echo "Running docker tag {{REPO_NAME}}:{{IMAGE_TAG}} {{ECR_REPO_URI}}:{{IMAGE_TAG}}"
docker tag {{REPO_NAME}}:{{IMAGE_TAG}} {{ECR_REPO_URI}}:{{IMAGE_TAG}}
if (!$LastExitCode -eq 0) {
  echo "Docker tag has failed."
  exit $LastExitCode
}
echo "Running docker push {{ECR_REPO_URI}}:{{IMAGE_TAG}}"
docker push {{ECR_REPO_URI}}:{{IMAGE_TAG}}
if ($LastExitCode -eq 0)
  {
    echo "ECR Container image setup succeeded."
  }
else 
  {
    echo "ECR Container image setup has failed."
  }

