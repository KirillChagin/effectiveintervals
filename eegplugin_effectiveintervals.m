function vers = eegplugin_calceffectiveintervals (fig, try_strings, catch_strings);
vers = 'effectiveintervals1.0';

toolsmenu = findobj(fig, 'tag', 'tools');
uimenu( toolsmenu, 'Label', 'Calculate effective intervals', 'separator', 'on', 'CallBack', 'EFFINTS = calceffectiveintervals(EEG)');

plotmenu = findobj(fig, 'tag', 'plot');
uimenu( plotmenu, 'Label', 'Plot effective intervals', 'separator', 'on', 'CallBack', 'effectiveintervalsgui(EEG, EFFINTS)');