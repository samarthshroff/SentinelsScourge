// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widget/SSWidget.h"

void USSWidget::SetWidgetController(UObject *Controller)
{
	WidgetController = Controller;
	WidgetControllerSet();
}
