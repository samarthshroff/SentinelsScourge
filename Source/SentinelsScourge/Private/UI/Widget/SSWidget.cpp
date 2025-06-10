// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#include "UI/Widget/SSWidget.h"

void USSWidget::SetWidgetController(UObject *Controller)
{
	WidgetController = Controller;
	WidgetControllerSet();
}
