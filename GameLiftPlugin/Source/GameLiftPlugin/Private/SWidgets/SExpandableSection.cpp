#include "SExpandableSection.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/SBoxPanel.h"

void SExpandableSection::Construct(const FArguments& InArgs)
{
    bAreaCollapsed = InArgs._InitiallyCollapsed;
    bAllowAnimatedTransition = InArgs._AllowAnimatedTransition;

    RolloutCurve = FCurveSequence(0.0f, 1.0f, ECurveEaseFunction::CubicOut);

    if (!bAreaCollapsed)
    {
        RolloutCurve.JumpToEnd();
    }

    ChildSlot
        [
            SNew(SVerticalBox)
                + SVerticalBox::Slot()
                [
                    InArgs._HeaderContent.Widget
                ]

                + SVerticalBox::Slot()
                .AutoHeight()
                [
                    SNew(SBorder)
                        .BorderBackgroundColor(FColor::Transparent)
                        .Visibility(this, &SExpandableSection::GetBodyVisibility)
                        .DesiredSizeScale(this, &SExpandableSection::GetSectionScale)
                        [
                            InArgs._BodyContent.Widget
                        ]
                ]
        ];
}

void SExpandableSection::SetExpanded(bool bExpanded)
{
    if (bAllowAnimatedTransition)
    {
        SetExpanded_Animated(bExpanded);
    }
    else
    {
        SetExpanded_Default(bExpanded);
    }
}

void SExpandableSection::SetExpanded_Default(bool bExpanded)
{
    if (bAreaCollapsed == bExpanded)
    {
        bAreaCollapsed = !bExpanded;

        if (bExpanded)
        {
            RolloutCurve.JumpToEnd();
        }
        else
        {
            RolloutCurve.JumpToStart();
        }

        OnExpansionChanged.ExecuteIfBound(bExpanded);
    }
}

void SExpandableSection::SetExpanded_Animated(bool bExpanded)
{
    if (bAreaCollapsed == bExpanded)
    {
        bAreaCollapsed = !bExpanded;

        if (!bAreaCollapsed)
        {
            RolloutCurve = FCurveSequence(0.0f, RolloutCurve.GetCurve(0).DurationSeconds, ECurveEaseFunction::CubicOut);
            RolloutCurve.Play(this->AsShared());
        }
        else
        {
            RolloutCurve = FCurveSequence(0.0f, RolloutCurve.GetCurve(0).DurationSeconds, ECurveEaseFunction::CubicIn);
            RolloutCurve.PlayReverse(this->AsShared());
        }

        OnExpansionChanged.ExecuteIfBound(!bAreaCollapsed);
    }
}

EVisibility SExpandableSection::GetBodyVisibility() const
{
    float Scale = GetSectionScale().Y;
    // The section is visible if its scale in Y is greater than 0
    return Scale > 0 ? EVisibility::Visible : EVisibility::Collapsed;
}

FVector2D SExpandableSection::GetSectionScale() const
{
    if (bAreaCollapsed)
    {
        return FVector2D(1.0f, 0.0f);
    }
    float Scale = RolloutCurve.GetLerp();
    return FVector2D(1.0f, Scale);
}
