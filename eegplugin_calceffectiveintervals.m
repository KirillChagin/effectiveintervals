function vers = eegplugin_calceffectiveintervals (fig, try_strings, catch_strings);
vers = 'calceffectiveintervals1.0';
plotmenu = findobj(fig, 'tag', 'plot');
uimenu( plotmenu, 'Label', 'Calculate effective intervals', 'CallBack', 'figure; plot(EEG.times, mean(EEG.data,3));');