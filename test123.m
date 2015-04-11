function [ersp,itc,powbase,times,freqs,erspboot,itcboot] =  test123(EEG)


icadata = (EEG.icaweights*EEG.icasphere)*EEG.data(EEG.icachansind,:);

tlimits = [-1000 2000];
num = 10;
cycles = [3 0.5];

pointrange1 = round(max((tlimits(1)/1000-EEG.xmin)*EEG.srate, 1));
pointrange2 = round(min((tlimits(2)/1000-EEG.xmin)*EEG.srate, EEG.pnts));
pointrange = [pointrange1:pointrange2];

tmpsig = (EEG.icaweights(num,:)*EEG.icasphere)*reshape(EEG.data(:,pointrange,:), EEG.nbchan, EEG.trials*length(pointrange));
tmpsig = reshape( tmpsig, length(num), size(tmpsig,2)*size(tmpsig,3));

options = [];
    if isfield(EEG.chanlocs, 'theta') && ~isempty(EEG.chanlocs(num).theta)
        if ~isfield(EEG, 'chaninfo'), EEG.chaninfo = []; end;
            options = [options ', ''topovec'', EEG.icawinv(:,' int2str(num) ...
                       '), ''elocs'', EEG.chanlocs, ''chaninfo'', EEG.chaninfo, ''caption'', [''IC '', num2str(num)], ''baseline'', [0], ''plotphase'', ''off'', ''padratio'', [1], ''timesout'', -1' ];
    end;
    
if EEG.xmin < 0
        fprintf('Computing window size in pop_newtimef based on half of the length of the baseline period');
        options = [ options ', ''winsize'', ' int2str(-EEG.xmin*EEG.srate) ];
    end;

    chanlabel = int2str(num);
figure; try, icadefs; set(gcf, 'color', BACKCOLOR); catch, end;


%newtimef( tmpsig(:, :), length(pointrange), [tlimits(1) tlimits(2)], EEG.srate, cycles, options);

com = sprintf('newtimef( tmpsig(:, :), length(pointrange), [tlimits(1) tlimits(2)], EEG.srate, cycles %s);', options);
[ersp,itc,powbase,times,freqs,erspboot,itcboot] = eval(com);

end