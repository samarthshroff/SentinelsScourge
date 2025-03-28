// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/VSCWidget.h"

void UVSCWidget::SetWidgetController(UVSCWidgetController* Controller)
{
	WidgetController = Controller;
	WidgetControllerSet();
}
