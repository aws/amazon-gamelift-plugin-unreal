﻿/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#pragma once
#include <aws/ssm/SSM_EXPORTS.h>
#include <aws/core/utils/memory/stl/AWSString.h>
#include <aws/ssm/model/PatchComplianceDataState.h>
#include <aws/core/utils/DateTime.h>
#include <utility>

namespace Aws
{
namespace Utils
{
namespace Json
{
  class JsonValue;
  class JsonView;
} // namespace Json
} // namespace Utils
namespace SSM
{
namespace Model
{

  /**
   * <p>Information about the state of a patch on a particular managed node as it
   * relates to the patch baseline used to patch the node.</p><p><h3>See Also:</h3>  
   * <a
   * href="http://docs.aws.amazon.com/goto/WebAPI/ssm-2014-11-06/PatchComplianceData">AWS
   * API Reference</a></p>
   */
  class PatchComplianceData
  {
  public:
    AWS_SSM_API PatchComplianceData();
    AWS_SSM_API PatchComplianceData(Aws::Utils::Json::JsonView jsonValue);
    AWS_SSM_API PatchComplianceData& operator=(Aws::Utils::Json::JsonView jsonValue);
    AWS_SSM_API Aws::Utils::Json::JsonValue Jsonize() const;


    ///@{
    /**
     * <p>The title of the patch.</p>
     */
    inline const Aws::String& GetTitle() const{ return m_title; }
    inline bool TitleHasBeenSet() const { return m_titleHasBeenSet; }
    inline void SetTitle(const Aws::String& value) { m_titleHasBeenSet = true; m_title = value; }
    inline void SetTitle(Aws::String&& value) { m_titleHasBeenSet = true; m_title = std::move(value); }
    inline void SetTitle(const char* value) { m_titleHasBeenSet = true; m_title.assign(value); }
    inline PatchComplianceData& WithTitle(const Aws::String& value) { SetTitle(value); return *this;}
    inline PatchComplianceData& WithTitle(Aws::String&& value) { SetTitle(std::move(value)); return *this;}
    inline PatchComplianceData& WithTitle(const char* value) { SetTitle(value); return *this;}
    ///@}

    ///@{
    /**
     * <p>The operating system-specific ID of the patch.</p>
     */
    inline const Aws::String& GetKBId() const{ return m_kBId; }
    inline bool KBIdHasBeenSet() const { return m_kBIdHasBeenSet; }
    inline void SetKBId(const Aws::String& value) { m_kBIdHasBeenSet = true; m_kBId = value; }
    inline void SetKBId(Aws::String&& value) { m_kBIdHasBeenSet = true; m_kBId = std::move(value); }
    inline void SetKBId(const char* value) { m_kBIdHasBeenSet = true; m_kBId.assign(value); }
    inline PatchComplianceData& WithKBId(const Aws::String& value) { SetKBId(value); return *this;}
    inline PatchComplianceData& WithKBId(Aws::String&& value) { SetKBId(std::move(value)); return *this;}
    inline PatchComplianceData& WithKBId(const char* value) { SetKBId(value); return *this;}
    ///@}

    ///@{
    /**
     * <p>The classification of the patch, such as <code>SecurityUpdates</code>,
     * <code>Updates</code>, and <code>CriticalUpdates</code>.</p>
     */
    inline const Aws::String& GetClassification() const{ return m_classification; }
    inline bool ClassificationHasBeenSet() const { return m_classificationHasBeenSet; }
    inline void SetClassification(const Aws::String& value) { m_classificationHasBeenSet = true; m_classification = value; }
    inline void SetClassification(Aws::String&& value) { m_classificationHasBeenSet = true; m_classification = std::move(value); }
    inline void SetClassification(const char* value) { m_classificationHasBeenSet = true; m_classification.assign(value); }
    inline PatchComplianceData& WithClassification(const Aws::String& value) { SetClassification(value); return *this;}
    inline PatchComplianceData& WithClassification(Aws::String&& value) { SetClassification(std::move(value)); return *this;}
    inline PatchComplianceData& WithClassification(const char* value) { SetClassification(value); return *this;}
    ///@}

    ///@{
    /**
     * <p>The severity of the patch such as <code>Critical</code>,
     * <code>Important</code>, and <code>Moderate</code>.</p>
     */
    inline const Aws::String& GetSeverity() const{ return m_severity; }
    inline bool SeverityHasBeenSet() const { return m_severityHasBeenSet; }
    inline void SetSeverity(const Aws::String& value) { m_severityHasBeenSet = true; m_severity = value; }
    inline void SetSeverity(Aws::String&& value) { m_severityHasBeenSet = true; m_severity = std::move(value); }
    inline void SetSeverity(const char* value) { m_severityHasBeenSet = true; m_severity.assign(value); }
    inline PatchComplianceData& WithSeverity(const Aws::String& value) { SetSeverity(value); return *this;}
    inline PatchComplianceData& WithSeverity(Aws::String&& value) { SetSeverity(std::move(value)); return *this;}
    inline PatchComplianceData& WithSeverity(const char* value) { SetSeverity(value); return *this;}
    ///@}

    ///@{
    /**
     * <p>The state of the patch on the managed node, such as INSTALLED or FAILED.</p>
     * <p>For descriptions of each patch state, see <a
     * href="https://docs.aws.amazon.com/systems-manager/latest/userguide/compliance-about.html#compliance-monitor-patch">About
     * patch compliance</a> in the <i>Amazon Web Services Systems Manager User
     * Guide</i>.</p>
     */
    inline const PatchComplianceDataState& GetState() const{ return m_state; }
    inline bool StateHasBeenSet() const { return m_stateHasBeenSet; }
    inline void SetState(const PatchComplianceDataState& value) { m_stateHasBeenSet = true; m_state = value; }
    inline void SetState(PatchComplianceDataState&& value) { m_stateHasBeenSet = true; m_state = std::move(value); }
    inline PatchComplianceData& WithState(const PatchComplianceDataState& value) { SetState(value); return *this;}
    inline PatchComplianceData& WithState(PatchComplianceDataState&& value) { SetState(std::move(value)); return *this;}
    ///@}

    ///@{
    /**
     * <p>The date/time the patch was installed on the managed node. Not all operating
     * systems provide this level of information.</p>
     */
    inline const Aws::Utils::DateTime& GetInstalledTime() const{ return m_installedTime; }
    inline bool InstalledTimeHasBeenSet() const { return m_installedTimeHasBeenSet; }
    inline void SetInstalledTime(const Aws::Utils::DateTime& value) { m_installedTimeHasBeenSet = true; m_installedTime = value; }
    inline void SetInstalledTime(Aws::Utils::DateTime&& value) { m_installedTimeHasBeenSet = true; m_installedTime = std::move(value); }
    inline PatchComplianceData& WithInstalledTime(const Aws::Utils::DateTime& value) { SetInstalledTime(value); return *this;}
    inline PatchComplianceData& WithInstalledTime(Aws::Utils::DateTime&& value) { SetInstalledTime(std::move(value)); return *this;}
    ///@}

    ///@{
    /**
     * <p>The IDs of one or more Common Vulnerabilities and Exposure (CVE) issues that
     * are resolved by the patch.</p>  <p>Currently, CVE ID values are reported
     * only for patches with a status of <code>Missing</code> or
     * <code>Failed</code>.</p> 
     */
    inline const Aws::String& GetCVEIds() const{ return m_cVEIds; }
    inline bool CVEIdsHasBeenSet() const { return m_cVEIdsHasBeenSet; }
    inline void SetCVEIds(const Aws::String& value) { m_cVEIdsHasBeenSet = true; m_cVEIds = value; }
    inline void SetCVEIds(Aws::String&& value) { m_cVEIdsHasBeenSet = true; m_cVEIds = std::move(value); }
    inline void SetCVEIds(const char* value) { m_cVEIdsHasBeenSet = true; m_cVEIds.assign(value); }
    inline PatchComplianceData& WithCVEIds(const Aws::String& value) { SetCVEIds(value); return *this;}
    inline PatchComplianceData& WithCVEIds(Aws::String&& value) { SetCVEIds(std::move(value)); return *this;}
    inline PatchComplianceData& WithCVEIds(const char* value) { SetCVEIds(value); return *this;}
    ///@}
  private:

    Aws::String m_title;
    bool m_titleHasBeenSet = false;

    Aws::String m_kBId;
    bool m_kBIdHasBeenSet = false;

    Aws::String m_classification;
    bool m_classificationHasBeenSet = false;

    Aws::String m_severity;
    bool m_severityHasBeenSet = false;

    PatchComplianceDataState m_state;
    bool m_stateHasBeenSet = false;

    Aws::Utils::DateTime m_installedTime;
    bool m_installedTimeHasBeenSet = false;

    Aws::String m_cVEIds;
    bool m_cVEIdsHasBeenSet = false;
  };

} // namespace Model
} // namespace SSM
} // namespace Aws
