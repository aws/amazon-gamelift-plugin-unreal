#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/Layout/SBorder.h"
#include "Animation/CurveSequence.h"
#include "Framework/SlateDelegates.h"

class SExpandableSection : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SExpandableSection)
        : _InitiallyCollapsed(false)
        , _AllowAnimatedTransition(false) {}

        SLATE_ARGUMENT(bool, InitiallyCollapsed)
        SLATE_EVENT(FOnBooleanValueChanged, OnExpansionChanged)
        SLATE_NAMED_SLOT(FArguments, HeaderContent)
        SLATE_NAMED_SLOT(FArguments, BodyContent)
        SLATE_ARGUMENT(bool, AllowAnimatedTransition)

    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

    void SetExpanded(bool bExpanded);

private:
    FVector2D GetSectionScale() const;
    EVisibility GetBodyVisibility() const;
    void SetExpanded_Default(bool bExpanded);
    void SetExpanded_Animated(bool bExpanded);

    bool bAreaCollapsed;
    bool bAllowAnimatedTransition;

    FCurveSequence RolloutCurve;
    FOnBooleanValueChanged OnExpansionChanged;
};