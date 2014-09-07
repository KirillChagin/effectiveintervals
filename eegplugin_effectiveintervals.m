function vers = eegplugin_effectiveintervals (fig, try_strings, catch_strings);
vers = 'effectiveintervals1.0';

toolsmenu = findobj(fig, 'tag', 'tools');
calceffintscallback = [ 'calcparams = effectiveintervalsgui;' ...
                     'timeinterval_left = 0; timeinterval_right = 0; eventtypes = {};' ...
                     'if length(calcparams) > 0' ...
                         'parsedinterval_left = str2num(calcparams.timeinterval_left);' ...
                         'if length(parsedinterval_left) > 0' ...
                            'timeinterval_left = parsedinterval_left(1);' ...
                         'end;' ...
                         'parsedinterval_right = str2num(calcparams.timeinterval_right);' ...
                         'if length(parsedinterval_right) > 0' ...
                            'timeinterval_right = parsedinterval_right(1);' ...
                         'end;' ...
                         'eventindexes = str2num(calcparams.eventtypes);' ...
                         'alltypes = getalleventtypes(EEG);' ...
                         'for i=1:length(eventindexes)' ...
                            'eventtypes(length(eventtypes)+1) = alltypes(eventindexes(i));' ...
                         'end;' ...
                         'clear parsedinterval_left;' ...
                         'clear parsedinterval_right;' ...
                         'clear eventindexes;' ...
                         'clear alltypes;' ...
                         'EFFINTS = calceffectiveintervals(EEG, eventtypes, timeinterval_left, timeinterval_right);' ... 
                     'end;' ...
                     'clear calcparams;' ... 
                     'clear timeinterval_left;' ...
                     'clear timeinterval_right;' ...
                     'clear eventtypes;' ...
                     ];
uimenu( toolsmenu, 'Label', 'Calculate effective intervals', 'separator', 'on', 'CallBack', calceffintscallback);

plotmenu = findobj(fig, 'tag', 'plot');
uimenu( plotmenu, 'Label', 'Plot effective intervals', 'separator', 'on', 'CallBack', 'ploteffectiveintervals(EEG, EFFINTS)');