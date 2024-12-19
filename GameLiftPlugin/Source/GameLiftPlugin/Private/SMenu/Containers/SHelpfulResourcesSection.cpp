#include "SHelpfulResourcesSection.h"
#include "SWidgets/SOnlineHyperlink.h"


#include <GameLiftPluginConstants.h>
#include <GameLiftPluginStyle.h>

#define LOCTEXT_NAMESPACE "SHelpfulResourcesSection"

void SHelpfulResourcesSection::Construct(const FArguments& InArgs)
{
	ChildSlot
		[
			SNew(SVerticalBox)
				// External links
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(SPadding::Top_Bottom)
				[
					SNew(SHorizontalBox)
						+ SHorizontalBox::Slot()
						.AutoWidth()
						.HAlign(HAlign_Left)
						[
							SNew(SOnlineHyperlink)
								.Text(Menu::DeployContainers::kLearnMoreAboutPrivateRepositoryLabel)
								//.Link(Url::kGameLiftDocumentationUrl)
						]
				]
		];
}

#undef LOCTEXT_NAMESPACE
