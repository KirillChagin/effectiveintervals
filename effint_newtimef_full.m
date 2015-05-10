function[effint_ersp, ersp,itc,powbase,times,freqs,erspboot,itcboot] = effint_newtimef_full(EEG, EFFINTS, comp_num, event_types, tlimits, cycles, varargin)

% Usage example:
%        >> [ersp,itc,powbase,times,freqs,erspboot,itcboot] = ...
%              effint_newtimef(EEG, EFFINTS, 10, ['S  1'; 'S  2'], [-1000 2000], cycles);
% For other input look at newtimef
    if nargin < 7
        cycles = [3 0.5];
    end
    
    if isnumeric(event_types(1))
        events = num2cell(event_types);
    else
        events = cellstr(event_types);
    end

    epoch_nums = cell(0);
    for i=1:length(EEG.epoch)
        contains = ismember(EEG.epoch(i).eventtype, events);
        include_epoch = 0;
        for j=1:length(contains)
            if (~isempty(contains) && contains(j) == 1)
                include_epoch = 1;
            end
        end

        if (include_epoch == 1)
            epoch_nums{length(epoch_nums) + 1} = i;
        end
    end

    mean_effint = get_mean_effint_for_component(EEG, EFFINTS, comp_num, events);

    if isempty(tlimits)
        tlimits = [EEG.xmin, EEG.xmax]*1000;
    end;	
    pointrange1 = round(max((tlimits(1)/1000-EEG.xmin)*EEG.srate, 1));
    pointrange2 = round(min((tlimits(2)/1000-EEG.xmin)*EEG.srate, EEG.pnts));
    pointrange = [pointrange1:pointrange2];
    
    tmpsig = (EEG.icaweights(comp_num,:)*EEG.icasphere)*reshape(EEG.data(:,pointrange,cell2mat(epoch_nums)), EEG.nbchan, length(epoch_nums)*length(pointrange));
    tmpsig = reshape( tmpsig, length(comp_num), size(tmpsig,2)*size(tmpsig,3));

    options = [];
   
    options = [ options ', ''baseline'', [0], ''plotphase'', ''off'', ''padratio'', [1], ''timesout'', -1, ''marktimes'', [mean_effint.left mean_effint.right] , varargin{:}' ];
    options = [ options ', ''winsize'', ' int2str(-EEG.xmin*EEG.srate) ];
    
    figure; try, icadefs; set(gcf, 'color', BACKCOLOR); catch, end;
    
    com = sprintf('newtimef(tmpsig(:, :),  length(pointrange), [tlimits(1) tlimits(2)], EEG.srate, cycles %s);', options);
    [ersp,itc,powbase,times,freqs,erspboot,itcboot] = eval(com);
    
    [~, left_ersp_index] = min(abs(times - mean_effint.left));
    [~, right_ersp_index] = min(abs(times - mean_effint.right));
    
    effint_ersp = ersp(:,left_ersp_index:right_ersp_index);
end

    