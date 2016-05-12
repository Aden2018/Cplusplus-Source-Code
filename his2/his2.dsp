# Microsoft Developer Studio Project File - Name="his2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=his2 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "his2.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "his2.mak" CFG="his2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "his2 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "his2 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "his2 - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /w /W0 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "his2 - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "his2 - Win32 Release"
# Name "his2 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AboutCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\AccountScale.cpp
# End Source File
# Begin Source File

SOURCE=.\AccrualAdd.cpp
# End Source File
# Begin Source File

SOURCE=.\AddHealth.cpp
# End Source File
# Begin Source File

SOURCE=.\AddHealthForModify.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseAddCash.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseChargeSet.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseOtherSickAdd.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseOtherSickSet.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseProjectSet.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseRyAdd.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseRyModify.cpp
# End Source File
# Begin Source File

SOURCE=.\BasisInsureList.cpp
# End Source File
# Begin Source File

SOURCE=.\BreadMedList.cpp
# End Source File
# Begin Source File

SOURCE=.\BreadMedQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\BreakMedOpe.cpp
# End Source File
# Begin Source File

SOURCE=.\ButtonEx.cpp
# End Source File
# Begin Source File

SOURCE=.\BuySellStockList.cpp
# End Source File
# Begin Source File

SOURCE=.\BuySellStockQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\CashBuySellStock.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartSell.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartYearDataAnalyse.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartYearDataCount.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeGysEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\CodeGysQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\ComBoxEx.cpp
# End Source File
# Begin Source File

SOURCE=.\CommonUse.cpp
# End Source File
# Begin Source File

SOURCE=.\CommonUseQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\CureList.cpp
# End Source File
# Begin Source File

SOURCE=.\DechargeScale.cpp
# End Source File
# Begin Source File

SOURCE=.\DepartSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DepartSetAdd.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogGhQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogInStorage.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogMedDL.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogMedModify.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogMedXL.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogQueryAAA.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogRoleset.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogSqlOutput.cpp
# End Source File
# Begin Source File

SOURCE=.\DMessageRead.cpp
# End Source File
# Begin Source File

SOURCE=.\DoctorMedUsed.cpp
# End Source File
# Begin Source File

SOURCE=.\DoctorWorkLoad.cpp
# End Source File
# Begin Source File

SOURCE=.\DoctorWorkOther.cpp
# End Source File
# Begin Source File

SOURCE=.\DSendNotify.cpp
# End Source File
# Begin Source File

SOURCE=.\DSRecive.cpp
# End Source File
# Begin Source File

SOURCE=.\EditEx.cpp
# End Source File
# Begin Source File

SOURCE=.\EditFlat.cpp
# End Source File
# Begin Source File

SOURCE=.\EmpBalanceCount.cpp
# End Source File
# Begin Source File

SOURCE=.\EmpDechargeQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\EmpGetAccount.cpp
# End Source File
# Begin Source File

SOURCE=.\Employee.cpp
# End Source File
# Begin Source File

SOURCE=.\EmployeeBmp.cpp
# End Source File
# Begin Source File

SOURCE=.\EmployeeDecharge.cpp
# End Source File
# Begin Source File

SOURCE=.\EmployeeModify.cpp
# End Source File
# Begin Source File

SOURCE=.\EmployeeNoworkQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\EmployeeQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\EmployeeQueryDecharge.cpp
# End Source File
# Begin Source File

SOURCE=.\EmployeeRelateQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\EmployeeRelateQueryForFee.cpp
# End Source File
# Begin Source File

SOURCE=.\EmpUsedAccountCollect.cpp
# End Source File
# Begin Source File

SOURCE=.\EverydayConsumeList.cpp
# End Source File
# Begin Source File

SOURCE=.\EverydayConsumeQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\excel9.cpp
# End Source File
# Begin Source File

SOURCE=.\FinanceReport.cpp
# End Source File
# Begin Source File

SOURCE=.\font.cpp
# End Source File
# Begin Source File

SOURCE=.\FormMedList.cpp
# End Source File
# Begin Source File

SOURCE=.\FormRkList.cpp
# End Source File
# Begin Source File

SOURCE=.\FormRkListQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\FormZkList.cpp
# End Source File
# Begin Source File

SOURCE=.\FormZkListQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\GenericMedCode.cpp
# End Source File
# Begin Source File

SOURCE=.\GenericStockMed.cpp
# End Source File
# Begin Source File

SOURCE=.\Gh.cpp
# End Source File
# Begin Source File

SOURCE=.\GhList.cpp
# End Source File
# Begin Source File

SOURCE=.\HealthSearch.cpp
# End Source File
# Begin Source File

SOURCE=.\his2.cpp
# End Source File
# Begin Source File

SOURCE=.\his2.rc
# End Source File
# Begin Source File

SOURCE=.\his2Doc.cpp
# End Source File
# Begin Source File

SOURCE=.\his2View.cpp
# End Source File
# Begin Source File

SOURCE=.\Hos30Factory.cpp
# End Source File
# Begin Source File

SOURCE=.\Hos30Hospital.cpp
# End Source File
# Begin Source File

SOURCE=.\Hos40Factory.cpp
# End Source File
# Begin Source File

SOURCE=.\HosDinner.cpp
# End Source File
# Begin Source File

SOURCE=.\HosElse.cpp
# End Source File
# Begin Source File

SOURCE=.\HosEmpCheck.cpp
# End Source File
# Begin Source File

SOURCE=.\HosEmpEdu.cpp
# End Source File
# Begin Source File

SOURCE=.\HosInstrumentGet.cpp
# End Source File
# Begin Source File

SOURCE=.\HosMedGet.cpp
# End Source File
# Begin Source File

SOURCE=.\HosModify.cpp
# End Source File
# Begin Source File

SOURCE=.\HosPlan.cpp
# End Source File
# Begin Source File

SOURCE=.\HosTuiXiu.cpp
# End Source File
# Begin Source File

SOURCE=.\HuaJia.cpp
# End Source File
# Begin Source File

SOURCE=.\HuaJiaList.cpp
# End Source File
# Begin Source File

SOURCE=.\JiHuaWeDecharge.cpp
# End Source File
# Begin Source File

SOURCE=.\LocalSetAdd.cpp
# End Source File
# Begin Source File

SOURCE=.\LocalSetModify.cpp
# End Source File
# Begin Source File

SOURCE=.\Logon.cpp
# End Source File
# Begin Source File

SOURCE=.\LogonList.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ManMedused.cpp
# End Source File
# Begin Source File

SOURCE=.\Mdiclient.cpp
# End Source File
# Begin Source File

SOURCE=.\MedCodeBase.cpp
# End Source File
# Begin Source File

SOURCE=.\MedcodeModify.cpp
# End Source File
# Begin Source File

SOURCE=.\MedCodeQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\MedDetail.cpp
# End Source File
# Begin Source File

SOURCE=.\MedRoomCompare.cpp
# End Source File
# Begin Source File

SOURCE=.\MedStockList.cpp
# End Source File
# Begin Source File

SOURCE=.\ModifyMedRec.cpp
# End Source File
# Begin Source File

SOURCE=.\MonthConsumeList.cpp
# End Source File
# Begin Source File

SOURCE=.\MoveKf.cpp
# End Source File
# Begin Source File

SOURCE=.\mschart.cpp
# End Source File
# Begin Source File

SOURCE=.\mshflexgrid.cpp
# End Source File
# Begin Source File

SOURCE=.\NewPersonalAddCash.cpp
# End Source File
# Begin Source File

SOURCE=.\NotifySet.cpp
# End Source File
# Begin Source File

SOURCE=.\OperatChargeRelateFee.cpp
# End Source File
# Begin Source File

SOURCE=.\OperatorAdd.cpp
# End Source File
# Begin Source File

SOURCE=.\OperatorSet.cpp
# End Source File
# Begin Source File

SOURCE=.\OtherDecharge.cpp
# End Source File
# Begin Source File

SOURCE=.\OtherDechargeQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\OtherHealth.cpp
# End Source File
# Begin Source File

SOURCE=.\OtherHealthForModify.cpp
# End Source File
# Begin Source File

SOURCE=.\OtherHealthSearch.cpp
# End Source File
# Begin Source File

SOURCE=.\OtherSickQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\Pandian.cpp
# End Source File
# Begin Source File

SOURCE=.\PandianList.cpp
# End Source File
# Begin Source File

SOURCE=.\PandianQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\PasswordChange.cpp
# End Source File
# Begin Source File

SOURCE=.\PasswordView.cpp
# End Source File
# Begin Source File

SOURCE=.\PayMed.cpp
# End Source File
# Begin Source File

SOURCE=.\PayMedFee.cpp
# End Source File
# Begin Source File

SOURCE=.\PayMedNum.cpp
# End Source File
# Begin Source File

SOURCE=.\PeculiarInput.cpp
# End Source File
# Begin Source File

SOURCE=.\picture.cpp
# End Source File
# Begin Source File

SOURCE=.\Progress.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgressEx.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgressIndicate.cpp
# End Source File
# Begin Source File

SOURCE=.\QiuXpButton.cpp
# End Source File
# Begin Source File

SOURCE=.\Query.cpp
# End Source File
# Begin Source File

SOURCE=.\QueryForCommonUseQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\QueryIC.cpp
# End Source File
# Begin Source File

SOURCE=.\QueryICList.cpp
# End Source File
# Begin Source File

SOURCE=.\QueryReadNotifyPeople.cpp
# End Source File
# Begin Source File

SOURCE=.\QueryRybm.cpp
# End Source File
# Begin Source File

SOURCE=.\RelateAdd.cpp
# End Source File
# Begin Source File

SOURCE=.\RelateCharge.cpp
# End Source File
# Begin Source File

SOURCE=.\RelateConsumeList.cpp
# End Source File
# Begin Source File

SOURCE=.\RelateModify.cpp
# End Source File
# Begin Source File

SOURCE=.\ResideAddPrice.cpp
# End Source File
# Begin Source File

SOURCE=.\ResideBedModify.cpp
# End Source File
# Begin Source File

SOURCE=.\ResideBedSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ResideBedSetAdd.cpp
# End Source File
# Begin Source File

SOURCE=.\ResideCheckIn.cpp
# End Source File
# Begin Source File

SOURCE=.\ResideCheckOut.cpp
# End Source File
# Begin Source File

SOURCE=.\ResideList.cpp
# End Source File
# Begin Source File

SOURCE=.\ResideListQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\ResideLocalSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ResidePriceQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\ResideUseMedQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\richtext.cpp
# End Source File
# Begin Source File

SOURCE=.\RollMed.cpp
# End Source File
# Begin Source File

SOURCE=.\RoomSet.cpp
# End Source File
# Begin Source File

SOURCE=.\RoomSetAdd.cpp
# End Source File
# Begin Source File

SOURCE=.\RoomSetModify.cpp
# End Source File
# Begin Source File

SOURCE=.\SearchMed.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectView.cpp
# End Source File
# Begin Source File

SOURCE=.\Splash.cpp
# End Source File
# Begin Source File

SOURCE=.\StandardSubsidy.cpp
# End Source File
# Begin Source File

SOURCE=.\StandardSubsidyAdd.cpp
# End Source File
# Begin Source File

SOURCE=.\StandardSubsidySet.cpp
# End Source File
# Begin Source File

SOURCE=.\StartDoctor.cpp
# End Source File
# Begin Source File

SOURCE=.\StaticDecharge.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StoreRoomEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\SubsidySet.cpp
# End Source File
# Begin Source File

SOURCE=.\Test.cpp
# End Source File
# Begin Source File

SOURCE=.\TreateList.cpp
# End Source File
# Begin Source File

SOURCE=.\TreateQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\UserMed.cpp
# End Source File
# Begin Source File

SOURCE=.\vcaxis.cpp
# End Source File
# Begin Source File

SOURCE=.\vcaxisgrid.cpp
# End Source File
# Begin Source File

SOURCE=.\vcaxisscale.cpp
# End Source File
# Begin Source File

SOURCE=.\vcaxistitle.cpp
# End Source File
# Begin Source File

SOURCE=.\vcbackdrop.cpp
# End Source File
# Begin Source File

SOURCE=.\vcbrush.cpp
# End Source File
# Begin Source File

SOURCE=.\vccategoryscale.cpp
# End Source File
# Begin Source File

SOURCE=.\vccolor.cpp
# End Source File
# Begin Source File

SOURCE=.\vccoor.cpp
# End Source File
# Begin Source File

SOURCE=.\vcdatagrid.cpp
# End Source File
# Begin Source File

SOURCE=.\vcdatapoint.cpp
# End Source File
# Begin Source File

SOURCE=.\vcdatapointlabel.cpp
# End Source File
# Begin Source File

SOURCE=.\vcdatapoints.cpp
# End Source File
# Begin Source File

SOURCE=.\vcfill.cpp
# End Source File
# Begin Source File

SOURCE=.\vcfont.cpp
# End Source File
# Begin Source File

SOURCE=.\vcfootnote.cpp
# End Source File
# Begin Source File

SOURCE=.\vcframe.cpp
# End Source File
# Begin Source File

SOURCE=.\vcintersection.cpp
# End Source File
# Begin Source File

SOURCE=.\vclabel.cpp
# End Source File
# Begin Source File

SOURCE=.\vclabels.cpp
# End Source File
# Begin Source File

SOURCE=.\vclcoor.cpp
# End Source File
# Begin Source File

SOURCE=.\vclegend.cpp
# End Source File
# Begin Source File

SOURCE=.\vclight.cpp
# End Source File
# Begin Source File

SOURCE=.\vclightsource.cpp
# End Source File
# Begin Source File

SOURCE=.\vclightsources.cpp
# End Source File
# Begin Source File

SOURCE=.\vclocation.cpp
# End Source File
# Begin Source File

SOURCE=.\vcmarker.cpp
# End Source File
# Begin Source File

SOURCE=.\vcpen.cpp
# End Source File
# Begin Source File

SOURCE=.\vcplot.cpp
# End Source File
# Begin Source File

SOURCE=.\vcplotbase.cpp
# End Source File
# Begin Source File

SOURCE=.\vcrect.cpp
# End Source File
# Begin Source File

SOURCE=.\vcseries.cpp
# End Source File
# Begin Source File

SOURCE=.\vcseriescollection.cpp
# End Source File
# Begin Source File

SOURCE=.\vcseriesmarker.cpp
# End Source File
# Begin Source File

SOURCE=.\vcseriesposition.cpp
# End Source File
# Begin Source File

SOURCE=.\vcshadow.cpp
# End Source File
# Begin Source File

SOURCE=.\vcstatline.cpp
# End Source File
# Begin Source File

SOURCE=.\vctextlayout.cpp
# End Source File
# Begin Source File

SOURCE=.\vctick.cpp
# End Source File
# Begin Source File

SOURCE=.\vctitle.cpp
# End Source File
# Begin Source File

SOURCE=.\vcvaluescale.cpp
# End Source File
# Begin Source File

SOURCE=.\vcview3d.cpp
# End Source File
# Begin Source File

SOURCE=.\vcwall.cpp
# End Source File
# Begin Source File

SOURCE=.\vcweighting.cpp
# End Source File
# Begin Source File

SOURCE=.\WageInput.cpp
# End Source File
# Begin Source File

SOURCE=.\YearDataCount.cpp
# End Source File
# Begin Source File

SOURCE=.\YearDataCountAnalyse.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AboutCtrl.h
# End Source File
# Begin Source File

SOURCE=.\AccountScale.h
# End Source File
# Begin Source File

SOURCE=.\AccrualAdd.h
# End Source File
# Begin Source File

SOURCE=.\AddHealth.h
# End Source File
# Begin Source File

SOURCE=.\AddHealthForModify.h
# End Source File
# Begin Source File

SOURCE=.\BaseAddCash.h
# End Source File
# Begin Source File

SOURCE=.\BaseChargeSet.h
# End Source File
# Begin Source File

SOURCE=.\BaseOtherSickAdd.h
# End Source File
# Begin Source File

SOURCE=.\BaseOtherSickSet.h
# End Source File
# Begin Source File

SOURCE=.\BaseProjectSet.h
# End Source File
# Begin Source File

SOURCE=.\BaseRyAdd.h
# End Source File
# Begin Source File

SOURCE=.\BaseRyModify.h
# End Source File
# Begin Source File

SOURCE=.\BasisInsureList.h
# End Source File
# Begin Source File

SOURCE=.\BreadMedList.h
# End Source File
# Begin Source File

SOURCE=.\BreadMedQuery.h
# End Source File
# Begin Source File

SOURCE=.\BreakMedOpe.h
# End Source File
# Begin Source File

SOURCE=.\ButtonEx.h
# End Source File
# Begin Source File

SOURCE=.\BuySellStockList.h
# End Source File
# Begin Source File

SOURCE=.\BuySellStockQuery.h
# End Source File
# Begin Source File

SOURCE=.\CashBuySellStock.h
# End Source File
# Begin Source File

SOURCE=.\ChartSell.h
# End Source File
# Begin Source File

SOURCE=.\ChartView.h
# End Source File
# Begin Source File

SOURCE=.\ChartYearDataAnalyse.h
# End Source File
# Begin Source File

SOURCE=.\ChartYearDataCount.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\CodeGysEdit.h
# End Source File
# Begin Source File

SOURCE=.\CodeGysQuery.h
# End Source File
# Begin Source File

SOURCE=.\ColorComboBox.h
# End Source File
# Begin Source File

SOURCE=.\ComBoxEx.h
# End Source File
# Begin Source File

SOURCE=.\CommonUse.h
# End Source File
# Begin Source File

SOURCE=.\CommonUseQuery.h
# End Source File
# Begin Source File

SOURCE=.\CureList.h
# End Source File
# Begin Source File

SOURCE=.\DechargeScale.h
# End Source File
# Begin Source File

SOURCE=.\DepartSet.h
# End Source File
# Begin Source File

SOURCE=.\DepartSetAdd.h
# End Source File
# Begin Source File

SOURCE=.\DialogGhQuery.h
# End Source File
# Begin Source File

SOURCE=.\DialogInStorage.h
# End Source File
# Begin Source File

SOURCE=.\DialogMedDL.h
# End Source File
# Begin Source File

SOURCE=.\DialogMedModify.h
# End Source File
# Begin Source File

SOURCE=.\DialogMedXL.h
# End Source File
# Begin Source File

SOURCE=.\DialogQueryAAA.h
# End Source File
# Begin Source File

SOURCE=.\DialogRoleset.h
# End Source File
# Begin Source File

SOURCE=.\DialogSqlOutput.h
# End Source File
# Begin Source File

SOURCE=.\DMessageRead.h
# End Source File
# Begin Source File

SOURCE=.\DoctorMedUsed.h
# End Source File
# Begin Source File

SOURCE=.\DoctorWorkLoad.h
# End Source File
# Begin Source File

SOURCE=.\DoctorWorkOther.h
# End Source File
# Begin Source File

SOURCE=.\DSendNotify.h
# End Source File
# Begin Source File

SOURCE=.\DSRecive.h
# End Source File
# Begin Source File

SOURCE=.\EditEx.h
# End Source File
# Begin Source File

SOURCE=.\EditFlat.h
# End Source File
# Begin Source File

SOURCE=.\EmpBalanceCount.h
# End Source File
# Begin Source File

SOURCE=.\EmpDechargeQuery.h
# End Source File
# Begin Source File

SOURCE=.\EmpGetAccount.h
# End Source File
# Begin Source File

SOURCE=.\Employee.h
# End Source File
# Begin Source File

SOURCE=.\EmployeeBmp.h
# End Source File
# Begin Source File

SOURCE=.\EmployeeDecharge.h
# End Source File
# Begin Source File

SOURCE=.\EmployeeModify.h
# End Source File
# Begin Source File

SOURCE=.\EmployeeNoworkQuery.h
# End Source File
# Begin Source File

SOURCE=.\EmployeeQuery.h
# End Source File
# Begin Source File

SOURCE=.\EmployeeQueryDecharge.h
# End Source File
# Begin Source File

SOURCE=.\EmployeeRelateQuery.h
# End Source File
# Begin Source File

SOURCE=.\EmployeeRelateQueryForFee.h
# End Source File
# Begin Source File

SOURCE=.\EmpUsedAccountCollect.h
# End Source File
# Begin Source File

SOURCE=.\EverydayConsumeList.h
# End Source File
# Begin Source File

SOURCE=.\EverydayConsumeQuery.h
# End Source File
# Begin Source File

SOURCE=.\excel9.h
# End Source File
# Begin Source File

SOURCE=.\FinanceReport.h
# End Source File
# Begin Source File

SOURCE=.\font.h
# End Source File
# Begin Source File

SOURCE=.\FormMedList.h
# End Source File
# Begin Source File

SOURCE=.\FormRkList.h
# End Source File
# Begin Source File

SOURCE=.\FormRkListQuery.h
# End Source File
# Begin Source File

SOURCE=.\FormZkList.h
# End Source File
# Begin Source File

SOURCE=.\FormZkListQuery.h
# End Source File
# Begin Source File

SOURCE=.\GenericMedCode.h
# End Source File
# Begin Source File

SOURCE=.\GenericStockMed.h
# End Source File
# Begin Source File

SOURCE=.\Gh.h
# End Source File
# Begin Source File

SOURCE=.\GhList.h
# End Source File
# Begin Source File

SOURCE=.\HealthSearch.h
# End Source File
# Begin Source File

SOURCE=.\his2.h
# End Source File
# Begin Source File

SOURCE=.\his2Doc.h
# End Source File
# Begin Source File

SOURCE=.\his2View.h
# End Source File
# Begin Source File

SOURCE=.\Hos30Factory.h
# End Source File
# Begin Source File

SOURCE=.\Hos30Hospital.h
# End Source File
# Begin Source File

SOURCE=.\Hos40Factory.h
# End Source File
# Begin Source File

SOURCE=.\HosDinner.h
# End Source File
# Begin Source File

SOURCE=.\HosElse.h
# End Source File
# Begin Source File

SOURCE=.\HosEmpCheck.h
# End Source File
# Begin Source File

SOURCE=.\HosEmpEdu.h
# End Source File
# Begin Source File

SOURCE=.\HosInstrumentGet.h
# End Source File
# Begin Source File

SOURCE=.\HosMedGet.h
# End Source File
# Begin Source File

SOURCE=.\HosModify.h
# End Source File
# Begin Source File

SOURCE=.\HosPlan.h
# End Source File
# Begin Source File

SOURCE=.\HosTuiXiu.h
# End Source File
# Begin Source File

SOURCE=.\HuaJia.h
# End Source File
# Begin Source File

SOURCE=.\HuaJiaList.h
# End Source File
# Begin Source File

SOURCE=.\JiHuaWeDecharge.h
# End Source File
# Begin Source File

SOURCE=.\LocalSetAdd.h
# End Source File
# Begin Source File

SOURCE=.\LocalSetModify.h
# End Source File
# Begin Source File

SOURCE=.\Logon.h
# End Source File
# Begin Source File

SOURCE=.\LogonList.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\ManMedused.h
# End Source File
# Begin Source File

SOURCE=.\Mdiclient.h
# End Source File
# Begin Source File

SOURCE=.\MedCodeBase.h
# End Source File
# Begin Source File

SOURCE=.\MedcodeModify.h
# End Source File
# Begin Source File

SOURCE=.\MedCodeQuery.h
# End Source File
# Begin Source File

SOURCE=.\MedDetail.h
# End Source File
# Begin Source File

SOURCE=.\MedRoomCompare.h
# End Source File
# Begin Source File

SOURCE=.\MedStockList.h
# End Source File
# Begin Source File

SOURCE=.\ModifyMedRec.h
# End Source File
# Begin Source File

SOURCE=.\MonthConsumeList.h
# End Source File
# Begin Source File

SOURCE=.\MoveKf.h
# End Source File
# Begin Source File

SOURCE=.\mschart.h
# End Source File
# Begin Source File

SOURCE=.\mshflexgrid.h
# End Source File
# Begin Source File

SOURCE=.\NewPersonalAddCash.h
# End Source File
# Begin Source File

SOURCE=.\NotifySet.h
# End Source File
# Begin Source File

SOURCE=.\OperatChargeRelateFee.h
# End Source File
# Begin Source File

SOURCE=.\OperatorAdd.h
# End Source File
# Begin Source File

SOURCE=.\OperatorSet.h
# End Source File
# Begin Source File

SOURCE=.\OtherDecharge.h
# End Source File
# Begin Source File

SOURCE=.\OtherDechargeQuery.h
# End Source File
# Begin Source File

SOURCE=.\OtherHealth.h
# End Source File
# Begin Source File

SOURCE=.\OtherHealthForModify.h
# End Source File
# Begin Source File

SOURCE=.\OtherHealthSearch.h
# End Source File
# Begin Source File

SOURCE=.\OtherSickQuery.h
# End Source File
# Begin Source File

SOURCE=.\Pandian.h
# End Source File
# Begin Source File

SOURCE=.\PandianList.h
# End Source File
# Begin Source File

SOURCE=.\PandianQuery.h
# End Source File
# Begin Source File

SOURCE=.\PasswordChange.h
# End Source File
# Begin Source File

SOURCE=.\PasswordView.h
# End Source File
# Begin Source File

SOURCE=.\PayMed.h
# End Source File
# Begin Source File

SOURCE=.\PayMedFee.h
# End Source File
# Begin Source File

SOURCE=.\PayMedNum.h
# End Source File
# Begin Source File

SOURCE=.\PeculiarInput.h
# End Source File
# Begin Source File

SOURCE=.\picture.h
# End Source File
# Begin Source File

SOURCE=.\Progress.h
# End Source File
# Begin Source File

SOURCE=.\ProgressEx.h
# End Source File
# Begin Source File

SOURCE=.\ProgressIndicate.h
# End Source File
# Begin Source File

SOURCE=.\QiuXpButton.h
# End Source File
# Begin Source File

SOURCE=.\Query.h
# End Source File
# Begin Source File

SOURCE=.\QueryForCommonUseQuery.h
# End Source File
# Begin Source File

SOURCE=.\QueryIC.h
# End Source File
# Begin Source File

SOURCE=.\QueryICList.h
# End Source File
# Begin Source File

SOURCE=.\QueryReadNotifyPeople.h
# End Source File
# Begin Source File

SOURCE=.\QueryRybm.h
# End Source File
# Begin Source File

SOURCE=.\RelateAdd.h
# End Source File
# Begin Source File

SOURCE=.\RelateCharge.h
# End Source File
# Begin Source File

SOURCE=.\RelateConsumeList.h
# End Source File
# Begin Source File

SOURCE=.\RelateModify.h
# End Source File
# Begin Source File

SOURCE=.\ResideAddPrice.h
# End Source File
# Begin Source File

SOURCE=.\ResideBedModify.h
# End Source File
# Begin Source File

SOURCE=.\ResideBedSet.h
# End Source File
# Begin Source File

SOURCE=.\ResideBedSetAdd.h
# End Source File
# Begin Source File

SOURCE=.\ResideCheckIn.h
# End Source File
# Begin Source File

SOURCE=.\ResideCheckOut.h
# End Source File
# Begin Source File

SOURCE=.\ResideList.h
# End Source File
# Begin Source File

SOURCE=.\ResideListQuery.h
# End Source File
# Begin Source File

SOURCE=.\ResideLocalSet.h
# End Source File
# Begin Source File

SOURCE=.\ResidePriceQuery.h
# End Source File
# Begin Source File

SOURCE=.\ResideUseMedQuery.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\richtext.h
# End Source File
# Begin Source File

SOURCE=.\RollMed.h
# End Source File
# Begin Source File

SOURCE=.\RoomSet.h
# End Source File
# Begin Source File

SOURCE=.\RoomSetAdd.h
# End Source File
# Begin Source File

SOURCE=.\RoomSetModify.h
# End Source File
# Begin Source File

SOURCE=.\SearchMed.h
# End Source File
# Begin Source File

SOURCE=.\SelectView.h
# End Source File
# Begin Source File

SOURCE=.\Splash.h
# End Source File
# Begin Source File

SOURCE=.\StandardSubsidy.h
# End Source File
# Begin Source File

SOURCE=.\StandardSubsidyAdd.h
# End Source File
# Begin Source File

SOURCE=.\StandardSubsidySet.h
# End Source File
# Begin Source File

SOURCE=.\StartDoctor.h
# End Source File
# Begin Source File

SOURCE=.\StaticDecharge.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StoreRoomEdit.h
# End Source File
# Begin Source File

SOURCE=.\SubsidySet.h
# End Source File
# Begin Source File

SOURCE=.\Test.h
# End Source File
# Begin Source File

SOURCE=.\TreateList.h
# End Source File
# Begin Source File

SOURCE=.\TreateQuery.h
# End Source File
# Begin Source File

SOURCE=.\UserMed.h
# End Source File
# Begin Source File

SOURCE=.\vcaxis.h
# End Source File
# Begin Source File

SOURCE=.\vcaxisgrid.h
# End Source File
# Begin Source File

SOURCE=.\vcaxisscale.h
# End Source File
# Begin Source File

SOURCE=.\vcaxistitle.h
# End Source File
# Begin Source File

SOURCE=.\vcbackdrop.h
# End Source File
# Begin Source File

SOURCE=.\vcbrush.h
# End Source File
# Begin Source File

SOURCE=.\vccategoryscale.h
# End Source File
# Begin Source File

SOURCE=.\vccolor.h
# End Source File
# Begin Source File

SOURCE=.\vccoor.h
# End Source File
# Begin Source File

SOURCE=.\vcdatagrid.h
# End Source File
# Begin Source File

SOURCE=.\vcdatapoint.h
# End Source File
# Begin Source File

SOURCE=.\vcdatapointlabel.h
# End Source File
# Begin Source File

SOURCE=.\vcdatapoints.h
# End Source File
# Begin Source File

SOURCE=.\vcfill.h
# End Source File
# Begin Source File

SOURCE=.\vcfont.h
# End Source File
# Begin Source File

SOURCE=.\vcfootnote.h
# End Source File
# Begin Source File

SOURCE=.\vcframe.h
# End Source File
# Begin Source File

SOURCE=.\vcintersection.h
# End Source File
# Begin Source File

SOURCE=.\vclabel.h
# End Source File
# Begin Source File

SOURCE=.\vclabels.h
# End Source File
# Begin Source File

SOURCE=.\vclcoor.h
# End Source File
# Begin Source File

SOURCE=.\vclegend.h
# End Source File
# Begin Source File

SOURCE=.\vclight.h
# End Source File
# Begin Source File

SOURCE=.\vclightsource.h
# End Source File
# Begin Source File

SOURCE=.\vclightsources.h
# End Source File
# Begin Source File

SOURCE=.\vclocation.h
# End Source File
# Begin Source File

SOURCE=.\vcmarker.h
# End Source File
# Begin Source File

SOURCE=.\vcpen.h
# End Source File
# Begin Source File

SOURCE=.\vcplot.h
# End Source File
# Begin Source File

SOURCE=.\vcplotbase.h
# End Source File
# Begin Source File

SOURCE=.\vcrect.h
# End Source File
# Begin Source File

SOURCE=.\vcseries.h
# End Source File
# Begin Source File

SOURCE=.\vcseriescollection.h
# End Source File
# Begin Source File

SOURCE=.\vcseriesmarker.h
# End Source File
# Begin Source File

SOURCE=.\vcseriesposition.h
# End Source File
# Begin Source File

SOURCE=.\vcshadow.h
# End Source File
# Begin Source File

SOURCE=.\vcstatline.h
# End Source File
# Begin Source File

SOURCE=.\vctextlayout.h
# End Source File
# Begin Source File

SOURCE=.\vctick.h
# End Source File
# Begin Source File

SOURCE=.\vctitle.h
# End Source File
# Begin Source File

SOURCE=.\vcvaluescale.h
# End Source File
# Begin Source File

SOURCE=.\vcview3d.h
# End Source File
# Begin Source File

SOURCE=.\vcwall.h
# End Source File
# Begin Source File

SOURCE=.\vcweighting.h
# End Source File
# Begin Source File

SOURCE=.\WageInput.h
# End Source File
# Begin Source File

SOURCE=.\YearDataCount.h
# End Source File
# Begin Source File

SOURCE=.\YearDataCountAnalyse.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\desktop_hospital.ico
# End Source File
# Begin Source File

SOURCE=.\res\emp.bmp
# End Source File
# Begin Source File

SOURCE=.\res\his2.ico
# End Source File
# Begin Source File

SOURCE=.\res\his2.rc2
# End Source File
# Begin Source File

SOURCE=.\res\logo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\logo2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\logo3.bmp
# End Source File
# Begin Source File

SOURCE=.\mdi.ico
# End Source File
# Begin Source File

SOURCE=".\res\Sci-FiObjects0092.ICO"
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section his2 : {E9E074D3-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcMarker
# 	2:10:HeaderFile:vcmarker.h
# 	2:8:ImplFile:vcmarker.cpp
# End Section
# Section his2 : {E9E0751B-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcAxisGrid
# 	2:10:HeaderFile:vcaxisgrid.h
# 	2:8:ImplFile:vcaxisgrid.cpp
# End Section
# Section his2 : {3A2B370C-BA0A-11D1-B137-0000F8753F5D}
# 	2:21:DefaultSinkHeaderFile:mschart.h
# 	2:16:DefaultSinkClass:CMSChart
# End Section
# Section his2 : {E9E074DA-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcBrush
# 	2:10:HeaderFile:vcbrush.h
# 	2:8:ImplFile:vcbrush.cpp
# End Section
# Section his2 : {E9E074FA-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcWeighting
# 	2:10:HeaderFile:vcweighting.h
# 	2:8:ImplFile:vcweighting.cpp
# End Section
# Section his2 : {E9A5593C-CAB0-11D1-8C0B-0000F8754DA1}
# 	2:5:Class:CRichText
# 	2:10:HeaderFile:richtext.h
# 	2:8:ImplFile:richtext.cpp
# End Section
# Section his2 : {E9E074EA-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcDataGrid
# 	2:10:HeaderFile:vcdatagrid.h
# 	2:8:ImplFile:vcdatagrid.cpp
# End Section
# Section his2 : {E9E0751F-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcTick
# 	2:10:HeaderFile:vctick.h
# 	2:8:ImplFile:vctick.cpp
# End Section
# Section his2 : {E9E07508-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLabel
# 	2:10:HeaderFile:vclabel.h
# 	2:8:ImplFile:vclabel.cpp
# End Section
# Section his2 : {E9E074EE-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLightSources
# 	2:10:HeaderFile:vclightsources.h
# 	2:8:ImplFile:vclightsources.cpp
# End Section
# Section his2 : {E9E07523-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcValueScale
# 	2:10:HeaderFile:vcvaluescale.h
# 	2:8:ImplFile:vcvaluescale.cpp
# End Section
# Section his2 : {E9E074DE-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcFill
# 	2:10:HeaderFile:vcfill.h
# 	2:8:ImplFile:vcfill.cpp
# End Section
# Section his2 : {E9E0750A-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLabels
# 	2:10:HeaderFile:vclabels.h
# 	2:8:ImplFile:vclabels.cpp
# End Section
# Section his2 : {E9E07513-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcSeriesCollection
# 	2:10:HeaderFile:vcseriescollection.h
# 	2:8:ImplFile:vcseriescollection.cpp
# End Section
# Section his2 : {0ECD9B64-23AA-11D0-B351-00A0C9055D8E}
# 	2:21:DefaultSinkHeaderFile:mshflexgrid.h
# 	2:16:DefaultSinkClass:CMSHFlexGrid
# End Section
# Section his2 : {E9E0752A-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcDataPoints
# 	2:10:HeaderFile:vcdatapoints.h
# 	2:8:ImplFile:vcdatapoints.cpp
# End Section
# Section his2 : {E9E074F2-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcView3d
# 	2:10:HeaderFile:vcview3d.h
# 	2:8:ImplFile:vcview3d.cpp
# End Section
# Section his2 : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
# Section his2 : {E9E074E2-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcBackdrop
# 	2:10:HeaderFile:vcbackdrop.h
# 	2:8:ImplFile:vcbackdrop.cpp
# End Section
# Section his2 : {E9E07517-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcCategoryScale
# 	2:10:HeaderFile:vccategoryscale.h
# 	2:8:ImplFile:vccategoryscale.cpp
# End Section
# Section his2 : {E9E074E6-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcFootnote
# 	2:10:HeaderFile:vcfootnote.h
# 	2:8:ImplFile:vcfootnote.cpp
# End Section
# Section his2 : {E9E07527-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcPlot
# 	2:10:HeaderFile:vcplot.h
# 	2:8:ImplFile:vcplot.cpp
# End Section
# Section his2 : {E9E0750E-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcDataPoint
# 	2:10:HeaderFile:vcdatapoint.h
# 	2:8:ImplFile:vcdatapoint.cpp
# End Section
# Section his2 : {3B7C8860-D78F-101B-B9B5-04021C009402}
# 	2:21:DefaultSinkHeaderFile:richtext.h
# 	2:16:DefaultSinkClass:CRichText
# End Section
# Section his2 : {E9E074D6-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLocation
# 	2:10:HeaderFile:vclocation.h
# 	2:8:ImplFile:vclocation.cpp
# End Section
# Section his2 : {E9E07502-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcSeriesPosition
# 	2:10:HeaderFile:vcseriesposition.h
# 	2:8:ImplFile:vcseriesposition.cpp
# End Section
# Section his2 : {E9E074D1-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcPen
# 	2:10:HeaderFile:vcpen.h
# 	2:8:ImplFile:vcpen.cpp
# End Section
# Section his2 : {E9E074CD-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcRect
# 	2:10:HeaderFile:vcrect.h
# 	2:8:ImplFile:vcrect.cpp
# End Section
# Section his2 : {3A2B370A-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CMSChart
# 	2:10:HeaderFile:mschart.h
# 	2:8:ImplFile:mschart.cpp
# End Section
# Section his2 : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture.h
# 	2:8:ImplFile:picture.cpp
# End Section
# Section his2 : {E9E07506-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcStatLine
# 	2:10:HeaderFile:vcstatline.h
# 	2:8:ImplFile:vcstatline.cpp
# End Section
# Section his2 : {E9E074DC-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcShadow
# 	2:10:HeaderFile:vcshadow.h
# 	2:8:ImplFile:vcshadow.cpp
# End Section
# Section his2 : {E9E0751D-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcIntersection
# 	2:10:HeaderFile:vcintersection.h
# 	2:8:ImplFile:vcintersection.cpp
# End Section
# Section his2 : {E9E07511-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcSeries
# 	2:10:HeaderFile:vcseries.h
# 	2:8:ImplFile:vcseries.cpp
# End Section
# Section his2 : {E9E07521-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcAxisScale
# 	2:10:HeaderFile:vcaxisscale.h
# 	2:8:ImplFile:vcaxisscale.cpp
# End Section
# Section his2 : {E9E074D5-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcTextLayout
# 	2:10:HeaderFile:vctextlayout.h
# 	2:8:ImplFile:vctextlayout.cpp
# End Section
# Section his2 : {E9E074EC-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLightSource
# 	2:10:HeaderFile:vclightsource.h
# 	2:8:ImplFile:vclightsource.cpp
# End Section
# Section his2 : {0ECD9B62-23AA-11D0-B351-00A0C9055D8E}
# 	2:5:Class:CMSHFlexGrid
# 	2:10:HeaderFile:mshflexgrid.h
# 	2:8:ImplFile:mshflexgrid.cpp
# End Section
# Section his2 : {E9E074E0-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcFrame
# 	2:10:HeaderFile:vcframe.h
# 	2:8:ImplFile:vcframe.cpp
# End Section
# Section his2 : {E9E074F0-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLight
# 	2:10:HeaderFile:vclight.h
# 	2:8:ImplFile:vclight.cpp
# End Section
# Section his2 : {E9E074FC-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcWall
# 	2:10:HeaderFile:vcwall.h
# 	2:8:ImplFile:vcwall.cpp
# End Section
# Section his2 : {E9E074C9-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcCoor
# 	2:10:HeaderFile:vccoor.h
# 	2:8:ImplFile:vccoor.cpp
# End Section
# Section his2 : {E9E07515-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcAxisTitle
# 	2:10:HeaderFile:vcaxistitle.h
# 	2:8:ImplFile:vcaxistitle.cpp
# End Section
# Section his2 : {E9E0750C-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcDataPointLabel
# 	2:10:HeaderFile:vcdatapointlabel.h
# 	2:8:ImplFile:vcdatapointlabel.cpp
# End Section
# Section his2 : {E9E07525-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcAxis
# 	2:10:HeaderFile:vcaxis.h
# 	2:8:ImplFile:vcaxis.cpp
# End Section
# Section his2 : {E9E074E4-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcTitle
# 	2:10:HeaderFile:vctitle.h
# 	2:8:ImplFile:vctitle.cpp
# End Section
# Section his2 : {E9E074F4-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcPlotBase
# 	2:10:HeaderFile:vcplotbase.h
# 	2:8:ImplFile:vcplotbase.cpp
# End Section
# Section his2 : {E9E074CB-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLCoor
# 	2:10:HeaderFile:vclcoor.h
# 	2:8:ImplFile:vclcoor.cpp
# End Section
# Section his2 : {E9E074CF-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcColor
# 	2:10:HeaderFile:vccolor.h
# 	2:8:ImplFile:vccolor.cpp
# End Section
# Section his2 : {E9E074D8-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcFont
# 	2:10:HeaderFile:vcfont.h
# 	2:8:ImplFile:vcfont.cpp
# End Section
# Section his2 : {E9E07504-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcSeriesMarker
# 	2:10:HeaderFile:vcseriesmarker.h
# 	2:8:ImplFile:vcseriesmarker.cpp
# End Section
# Section his2 : {E9E074E8-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLegend
# 	2:10:HeaderFile:vclegend.h
# 	2:8:ImplFile:vclegend.cpp
# End Section
