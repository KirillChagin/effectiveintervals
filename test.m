function test(EEG)


intervals = getintervals(EEG);
interval = intervals{1,13};

tlimits = [0 length(interval)];
num = 10;
cycles = [3 0.5];

pointrange1 = round(max((tlimits(1)/1000-EEG.xmin)*EEG.srate, 1));
pointrange2 = round(min((tlimits(2)/1000-EEG.xmin)*EEG.srate, EEG.pnts));
pointrange = [pointrange1:pointrange2];

% tmpsig = (EEG.icaweights(num,:)*EEG.icasphere)*reshape(EEG.data(:,pointrange,:), EEG.nbchan, EEG.trials*length(pointrange));
% tmpsig = reshape( tmpsig, length(num), size(tmpsig,2)*size(tmpsig,3));

options = [];
%     if isfield(EEG.chanlocs, 'theta') && ~isempty(EEG.chanlocs(num).theta)
%         if ~isfield(EEG, 'chaninfo'), EEG.chaninfo = []; end;
%             options = [options ', ''topovec'', EEG.icawinv(:,' int2str(num) ...
%                        '), ''elocs'', EEG.chanlocs, ''chaninfo'', EEG.chaninfo, ''caption'', [''IC '', num2str(num)], ''baseline'', [0], ''plotphase'', ''off'', ''padratio'', [1], ''timesout'', -1' ];
%     end;
%     
% if EEG.xmin < 0
%         fprintf('Computing window size in pop_newtimef based on half of the length of the baseline period');
%         options = [ options ', ''winsize'', ' '400' ];
%     end;

%     chanlabel = int2str(num);
% figure; try, icadefs; set(gcf, 'color', BACKCOLOR); catch, end;

tmpsig = interval(1,:);

%newtimef( tmpsig(:, :), length(pointrange), [tlimits(1) tlimits(2)], EEG.srate, cycles, options);

%       'plotersp'  = ['on'|'off'] Plot power spectral perturbations    {'on'}
%       'plotitc'   = ['on'|'off'] Plot inter-trial coherence           {'on'}
%       'plotphasesign' = ['on'|'off'] Plot phase sign in the inter trial coherence {'on'}

options = [ options ', ''plotersp'',  ''off'',  ''plotitc'',  ''off'', ''plotphasesign'',  ''off'', ''baseline'', [0], ''plotphase'', ''off'', ''padratio'', [1], ''timesout'', -1' ];
 
com = sprintf('newtimef( tmpsig, length(tmpsig), [tlimits(1) tlimits(2)], EEG.srate, cycles %s);', options);
[evalout, ersp,itc,powbase,times,freqs,erspboot,itcboot] = evalc(com);

ersp_size = size(ersp);
nfreqs = ersp_size(1);
timesout = ersp_size(2);

for i=1:nfreqs
    effint = effectiveinterval(ersp(i,:), 10000, 1, -1, 10000, 1, 3);
    
    left = effint.left
    right = effint.right
    negentropy = effint.negentropy
    
    a = 0
end
timesout
length(times)
times
end


















