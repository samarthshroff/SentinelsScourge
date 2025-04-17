// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/VSWidget.h"

void UVSWidget::SetWidgetController(UObject* Controller)
{
	WidgetController = Controller;
	WidgetControllerSet();
}
