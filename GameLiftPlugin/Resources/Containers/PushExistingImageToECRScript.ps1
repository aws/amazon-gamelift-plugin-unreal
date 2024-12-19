$ErrorActionPreference="Stop"
echo "Running aws ecr get-login-password --region {{REGION}} --profile {{PROFILE_NAME}} | docker login --username AWS --password-stdin {{ECR_REGISTRY_URL}}"
aws ecr get-login-password --region {{REGION}} --profile {{PROFILE_NAME}} | docker login --username AWS --password-stdin {{ECR_REGISTRY_URL}}
if (!$LastExitCode -eq 0) {
  echo "Docker login has failed."
  exit $LastExitCode
}
echo "Running docker tag {{IMAGE_ID}} {{ECR_REPO_URI}}:{{IMAGE_TAG}}"
docker tag {{IMAGE_ID}} {{ECR_REPO_URI}}:{{IMAGE_TAG}}
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

