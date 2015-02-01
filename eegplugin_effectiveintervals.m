function vers = eegplugin_effectiveintervals (fig, try_strings, catch_strings);
vers = 'effectiveintervals1.0';

toolsmenu = findobj(fig, 'tag', 'tools');
calceffintscallback = [ 'calcparams = effectiveintervalsgui;' ...
                     'timeinterval_left = 0; timeinterval_right = 0; constraint_left = 0; constraint_right = 0; superiority_coef = 1; min_int_len = 0; eventtypes = {};' ...
                     'if length(calcparams) > 0' ...
                         'parsedinterval_left = str2num(calcparams.timeinterval_left);' ...
                         'if length(parsedinterval_left) > 0' ...
                            'timeinterval_left = parsedinterval_left(1);' ...
                         'end;' ...
                         'parsedinterval_right = str2num(calcparams.timeinterval_right);' ...
                         'if length(parsedinterval_right) > 0' ...
                            'timeinterval_right = parsedinterval_right(1);' ...
                         'end;' ...
                         'parsedconstraint_left = str2num(calcparams.constraint_left);' ...
                         'if length(parsedconstraint_left) > 0' ...
                            'constraint_left = parsedconstraint_left(1);' ...
                         'end;' ...
                         'parsedconstraint_right = str2num(calcparams.constraint_right);' ...
                         'if length(parsedconstraint_right) > 0' ...
                            'constraint_right = parsedconstraint_right(1);' ...
                         'end;' ...
                         'parsedsuperiority_coef = str2num(calcparams.superiority_coef);' ...
                         'if length(parsedsuperiority_coef) > 0' ...
                            'superiority_coef = parsedsuperiority_coef(1);' ...
                         'end;' ...
                         'parsedmin_int_len = str2num(calcparams.min_int_len);' ...
                         'if length(parsedmin_int_len) > 0' ...
                            'min_int_len = parsedmin_int_len(1);' ...
                         'end;' ...
                         'eventindexes = str2num(calcparams.eventtypes);' ...
                         'alltypes = getalleventtypes(EEG);' ...
                         'for i=1:length(eventindexes)' ...
                            'eventtypes(length(eventtypes)+1) = alltypes(eventindexes(i));' ...
                         'end;' ...
                         'clear parsedinterval_left;' ...
                         'clear parsedinterval_right;' ...
                         'clear parsedconstraint_left;' ...
                         'clear parsedconstraint_right;' ...
                         'clear parsedsuperiority_coef;' ...
                         'clear parsedmin_int_len;' ...
                         'clear eventindexes;' ...
                         'clear alltypes;' ...
                         'EFFINTS = calceffectiveintervals(EEG, eventtypes, timeinterval_left, timeinterval_right, constraint_left, constraint_right, superiority_coef, min_int_len);' ... 
                     'end;' ...
                     'clear calcparams;' ... 
                     'clear timeinterval_left;' ...
                     'clear timeinterval_right;' ...
                     'clear constraint_left;' ...
                     'clear constraint_right;' ...
                     'clear superiority_coef;' ...
                     'clear min_int_len;' ...
                     'clear eventtypes;' ...
                     ];

lazarenko_calceffintscallback = [ 'calcparams = effectiveintervalsgui;' ...
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
                         'EFFINTSLAZ = lazorenko_calceffectiveintervals(EEG, eventtypes, timeinterval_left, timeinterval_right);' ... 
                     'end;' ...
                     'clear calcparams;' ... 
                     'clear timeinterval_left;' ...
                     'clear timeinterval_right;' ...
                     'clear eventtypes;' ...
                     ];
lazarenko_plot_callback = [ 'plotparams = selected_channels_gui;' ...
                     'if length(plotparams) > 0' ...
                         'chan_types = str2num(plotparams.chantypes);' ...
                         'lazarenko_ploteffectiveintervals(EEG, EFFINTSLAZ, chan_types);' ... 
                     'end;' ...
                     ];
plot_callback = [ 'plotparams = selected_channels_gui;' ...
                     'if length(plotparams) > 0' ...
                         'chan_types = str2num(plotparams.chantypes);' ...
                         'ploteffectiveintervals(EEG, EFFINTS, chan_types);' ... 
                     'end;' ...
                     ];
                 
uimenu( toolsmenu, 'Label', 'Calculate effective intervals', 'separator', 'on', 'CallBack', calceffintscallback);
uimenu( toolsmenu, 'Label', 'Lazarenko effective intervals', 'separator', 'off', 'CallBack', lazarenko_calceffintscallback);
plotmenu = findobj(fig, 'tag', 'plot');
uimenu( plotmenu, 'Label', 'Plot effective intervals', 'separator', 'on', 'CallBack', plot_callback);
uimenu( plotmenu, 'Label', 'Plot Lazarenko effective intervals', 'separator', 'off', 'CallBack', lazarenko_plot_callback);