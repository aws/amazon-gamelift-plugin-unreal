﻿/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#pragma once
#include <aws/ssm/SSM_EXPORTS.h>
#include <aws/core/utils/memory/stl/AWSString.h>
#include <utility>

namespace Aws
{
template<typename RESULT_TYPE>
class AmazonWebServiceResult;

namespace Utils
{
namespace Json
{
  class JsonValue;
} // namespace Json
} // namespace Utils
namespace SSM
{
namespace Model
{
  class CreateActivationResult
  {
  public:
    AWS_SSM_API CreateActivationResult();
    AWS_SSM_API CreateActivationResult(const Aws::AmazonWebServiceResult<Aws::Utils::Json::JsonValue>& result);
    AWS_SSM_API CreateActivationResult& operator=(const Aws::AmazonWebServiceResult<Aws::Utils::Json::JsonValue>& result);


    ///@{
    /**
     * <p>The ID number generated by the system when it processed the activation. The
     * activation ID functions like a user name.</p>
     */
    inline const Aws::String& GetActivationId() const{ return m_activationId; }
    inline void SetActivationId(const Aws::String& value) { m_activationId = value; }
    inline void SetActivationId(Aws::String&& value) { m_activationId = std::move(value); }
    inline void SetActivationId(const char* value) { m_activationId.assign(value); }
    inline CreateActivationResult& WithActivationId(const Aws::String& value) { SetActivationId(value); return *this;}
    inline CreateActivationResult& WithActivationId(Aws::String&& value) { SetActivationId(std::move(value)); return *this;}
    inline CreateActivationResult& WithActivationId(const char* value) { SetActivationId(value); return *this;}
    ///@}

    ///@{
    /**
     * <p>The code the system generates when it processes the activation. The
     * activation code functions like a password to validate the activation ID. </p>
     */
    inline const Aws::String& GetActivationCode() const{ return m_activationCode; }
    inline void SetActivationCode(const Aws::String& value) { m_activationCode = value; }
    inline void SetActivationCode(Aws::String&& value) { m_activationCode = std::move(value); }
    inline void SetActivationCode(const char* value) { m_activationCode.assign(value); }
    inline CreateActivationResult& WithActivationCode(const Aws::String& value) { SetActivationCode(value); return *this;}
    inline CreateActivationResult& WithActivationCode(Aws::String&& value) { SetActivationCode(std::move(value)); return *this;}
    inline CreateActivationResult& WithActivationCode(const char* value) { SetActivationCode(value); return *this;}
    ///@}

    ///@{
    
    inline const Aws::String& GetRequestId() const{ return m_requestId; }
    inline void SetRequestId(const Aws::String& value) { m_requestId = value; }
    inline void SetRequestId(Aws::String&& value) { m_requestId = std::move(value); }
    inline void SetRequestId(const char* value) { m_requestId.assign(value); }
    inline CreateActivationResult& WithRequestId(const Aws::String& value) { SetRequestId(value); return *this;}
    inline CreateActivationResult& WithRequestId(Aws::String&& value) { SetRequestId(std::move(value)); return *this;}
    inline CreateActivationResult& WithRequestId(const char* value) { SetRequestId(value); return *this;}
    ///@}
  private:

    Aws::String m_activationId;

    Aws::String m_activationCode;

    Aws::String m_requestId;
  };

} // namespace Model
} // namespace SSM
} // namespace Aws
