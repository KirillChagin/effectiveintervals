function ploteffectiveintervals(EEG, effints, chantypes)
chantypes
effintssize = size(effints);
fullsize = effintssize(1) * effintssize(2);
winrej = zeros(fullsize, effintssize(1) + 5);
for i=1:effintssize(2)
    for j=1:effintssize(1)
        if (any(chantypes == j))
            effint = effints{j,i};
            left = effint.offset + effint.left;
            right = effint.offset + effint.right;
            channels = zeros(1,effintssize(1));
            channels(j) = 1;
            ind = (i-1)*effintssize(2) + j;
            winrej(ind,1:5) = [left right 1 1 1];
            winrej(ind,6:end) = channels;
        end
    end;
end;

pop_eegplot_wrapper( EEG, 0, 1, 1, 1, 'winrej', winrej);

% icadata = (EEG.icaweights*EEG.icasphere)*EEG.data(EEG.icachansind,:);
% eegplot(icadata, 'srate', EEG.srate, 'title', 'Scroll component activities -- eegplot()', ...
% 			 'limits', [EEG.xmin EEG.xmax]*1000, 'command', command, 'winrej',winrej, 'events', EEG.event); 
         
% 


% epoch = 1:EEG.trials;
% chanind = 1:EEG.nbchan;
% epochchanind = zeros(EEG.trials, EEG.nbchan);
% for i=1:EEG.trials
%     for j=1:EEG.nbchan
%         epochchanind(i,j) = chanind(j);
%     end;
% end;
% 
% 
% rejepochcol =  [0.95, 0.95, 0.95];
% rejepoch = zeros(1,EEG.trials);
% rejepoch(epoch) = ones(1,length(epoch));
% rejepochE = ones(EEG.nbchan,EEG.trials);
% 
% winrej=effints2eegplot(rejepoch,rejepochE,EEG.pnts,rejepochcol);
% winrej
% pop_eegplot( EEG, 0, 1, 1, 1, 'winrej', winrej);
         



% %simple plot
% 
% function ploteffectiveintervals(EEG, effints)
% 
% effintssize = size(effints);
% fullsize = effintssize(1) * effintssize(2);
% winrej = zeros(fullsize, effintssize(1) + 5);
% for i=1:effintssize(2)
%     for j=1:effintssize(1)
%         effint = effints{j,i};
%         left = effint.offset + effint.left;
%         right = effint.offset + effint.right;
%         channels = zeros(1,effintssize(1));
%         channels(j) = 1;
%         ind = (i-1)*effintssize(2) + j;
%         winrej(ind,1:5) = [left right 1 1 1];
%         winrej(ind,6:end) = channels;
%     end;
% end;
% 
% icadata = (EEG.icaweights*EEG.icasphere)*EEG.data(EEG.icachansind,:);
% eegplot(icadata, 'srate', EEG.srate, 'title', 'Scroll component activities -- eegplot()', ...
% 			 'limits', [EEG.xmin EEG.xmax]*1000,'winrej',winrej, 'events', EEG.event); 


% 
% % pop_eegplot() - Visually inspect EEG data using a scrolling display.
% %                 Perform rejection or marking for rejection of visually 
% %                 (and/or previously) selected data portions (i.e., stretches 
% %                 of continuous data or whole data epochs).
% % Usage:
% %   >> pop_eegplot( EEG ) % Scroll EEG channel data. Allow marking for rejection via
% %                         % button 'Update Marks' but perform no actual data rejection.
% %                         % Do not show or use marks from previous visual inspections
% %                         % or from semi-auotmatic rejection.
% %   >> pop_eegplot( EEG, typerej, superpose, reject );
% %
% % Graphic interface:
% %   "Add to previously marked rejections" - [edit box] Either YES or NO. 
% %                    Command line equivalent: 'superpose'.
% %   "Reject marked trials" - [edit box] Either YES or NO. Command line
% %                    equivalent 'reject'.
% % Inputs:
% %   EEG        - input EEG dataset
% %   typerej    - type of rejection 0 = independent components; 
% %                                  1 = data channels. {Default: 1 = data channels}
% %   superpose  - 0 = Show new marks only: Do not color the background of data portions 
% %                    previously marked for rejection by visual inspection. Mark new data 
% %                    portions for rejection by first coloring them (by dragging the left 
% %                    mouse button), finally pressing the 'Update Marks' or 'Reject' 
% %                    buttons (see 'reject' below). Previous markings from visual inspection 
% %                    will be lost.
% %                1 = Show data portions previously marked by visual inspection plus 
% %                    data portions selected in this window for rejection (by dragging 
% %                    the left mouse button in this window). These are differentiated 
% %                    using a lighter and darker hue, respectively). Pressing the 
% %                    'Update Marks' or 'Reject' buttons (see 'reject' below)
% %                    will then mark or reject all the colored data portions.
% %                {Default: 0, show and act on new marks only}
% %   reject     - 0 = Mark for rejection. Mark data portions by dragging the left mouse 
% %                    button on the data windows (producing a background coloring indicating 
% %                    the extent of the marked data portion).  Then press the screen button 
% %                    'Update Marks' to store the data portions marked for rejection 
% %                    (stretches of continuous data or whole data epochs). No 'Reject' button 
% %                    is present, so data marked for rejection cannot be actually rejected 
% %                    from this eegplot() window. 
% %                1 = Reject marked trials. After inspecting/selecting data portions for
% %                    rejection, press button 'Reject' to reject (remove) them from the EEG 
% %                    dataset (i.e., those portions plottted on a colored background. 
% %                    {default: 0, mark for rejection only}
% % Outputs:
% %   Modifications are applied to the current EEG dataset at the end of the
% %   eegplot() call, when the user presses the 'Update Marks' or 'Reject' button.
% %   NOTE: The modifications made are not saved into EEGLAB history. As of v4.2,
% %   events contained in rejected data portions are remembered in the EEG.urevent
% %   structure (see EEGLAB tutorial).
% %
% % Author: Arnaud Delorme, CNL / Salk Institute, 2001
% %
% % See also: eeglab(), eegplot(), pop_rejepoch()
% 
% % Copyright (C) 2001 Arnaud Delorme, Salk Institute, arno@salk.edu
% %
% % This program is free software; you can redistribute it and/or modify
% % it under the terms of the GNU General Public License as published by
% % the Free Software Foundation; either version 2 of the License, or
% % (at your option) any later version.
% %
% % This program is distributed in the hope that it will be useful,
% % but WITHOUT ANY WARRANTY; without even the implied warranty of
% % MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
% % GNU General Public License for more details.
% %
% % You should have received a copy of the GNU General Public License
% % along with this program; if not, write to the Free Software
% % Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
% 
% % 01-25-02 reformated help & license -ad 
% % 03-07-02 added srate argument to eegplot call -ad
% % 03-27-02 added event latency recalculation for continuous data -ad
% 
% function ploteffectiveintervals(EEG, effints, icacomp, superpose, reject, topcommand, varargin)
% 
% com = '';
% if nargin < 1
% 	disp('Error: you must run Calculate effective intervals first');
% 	return;
% end;
% if nargin < 2
% 	help pop_eegplot;
% 	return;
% end;	
% if nargin < 3
% 	icacomp = 1;
% end;	
% if nargin < 2
% 	superpose = 0;
% end;
% if nargin < 5
% 	reject = 1;
% end;
% if icacomp == 0
% 	if isempty( EEG.icasphere )
% 		disp('Error: you must run ICA first'); return;
% 	end;
% end;
% 
% if nargin < 3 & EEG.trials > 1
% 
% 	% which set to save
% 	% -----------------
%     uilist       = { { 'style' 'text' 'string' 'Add to previously marked rejections? (checked=yes)'} , ...
%          	         { 'style' 'checkbox' 'string' '' 'value' 1 } , ...
%                      { 'style' 'text' 'string' 'Reject marked trials? (checked=yes)'} , ...
%          	         { 'style' 'checkbox' 'string' '' 'value' 0 } };
%     result = inputgui( { [ 2 0.2] [ 2 0.2]} , uilist, 'pophelp(''pop_eegplot'');', ...
%                        fastif(icacomp==0, 'Manual component rejection -- pop_eegplot()', ...
% 								'Reject epochs by visual inspection -- pop_eegplot()'));
% 	size_result  = size( result );
% 	if size_result(1) == 0 return; end;
%    
%    if result{1}, superpose=1; end;
%    if ~result{2}, reject=0; end;
% 
% end;
% 
% if EEG.trials > 1
%     if icacomp == 1 macrorej  = 'EEG.reject.rejmanual';
%         			macrorejE = 'EEG.reject.rejmanualE';
%     else			macrorej  = 'EEG.reject.icarejmanual';
%         			macrorejE = 'EEG.reject.icarejmanualE';
%     end;
%     if icacomp == 1
%          elecrange = [1:EEG.nbchan];
%     else elecrange = [1:size(EEG.icaweights,1)];
%     end;
%     colrej = EEG.reject.rejmanualcol;
% 	rej  = eval(macrorej);
% 	rejE = eval(macrorejE);
% 	
% 	eeg_rejmacro; % script macro for generating command and old rejection arrays
% 
% else % case of a single trial (continuous data)
% 	     %if icacomp, 
%     	 %    	command = ['if isempty(EEG.event) EEG.event = [eegplot2event(TMPREJ, -1)];' ...
%          %         'else EEG.event = [EEG.event(find(EEG.event(:,1) ~= -1),:); eegplot2event(TMPREJ, -1, [], [0.8 1 0.8])];' ...
%          %         'end;']; 
%       	 %else, command = ['if isempty(EEG.event) EEG.event = [eegplot2event(TMPREJ, -1)];' ...
%          %         'else EEG.event = [EEG.event(find(EEG.event(:,1) ~= -2),:); eegplot2event(TMPREJ, -1, [], [0.8 1 0.8])];' ...
%          %         'end;']; 
%       	 %end;
%          %if reject
%          %   command = ...
%          %   [  command ...
%          %      '[EEG.data EEG.xmax] = eegrej(EEG.data, EEG.event(find(EEG.event(:,1) < 0),3:end), EEG.xmax-EEG.xmin);' ...
%          %      'EEG.xmax = EEG.xmax+EEG.xmin;' ...
%          %   	'EEG.event = EEG.event(find(EEG.event(:,1) >= 0),:);' ...
%          %      'EEG.icaact = [];' ...
%          %      'EEG = eeg_checkset(EEG);' ];
%     eeglab_options; % changed from eeglaboptions 3/30/02 -sm
%     if reject == 0, command = [];
%     else
%         command = ...
%             [  '[EEGTMP LASTCOM] = eeg_eegrej(EEG,eegplot2event(TMPREJ, -1));' ...
%                'if ~isempty(LASTCOM),' ... 
%                '  [ALLEEG EEG CURRENTSET tmpcom] = pop_newset(ALLEEG, EEGTMP, CURRENTSET);' ...
%                '  if ~isempty(tmpcom),' ... 
%                '     EEG = eegh(LASTCOM, EEG);' ...
%                '     eegh(tmpcom);' ...
%                '     eeglab(''redraw'');' ...
%                '  end;' ...
%                'end;' ...
%                'clear EEGTMP tmpcom;' ];
%         if nargin < 4
%             res = questdlg2( strvcat('Mark stretches of continuous data for rejection', ...
%                                      'by dragging the left mouse button. Click on marked', ...
%                                      'stretches to unmark. When done,press "REJECT" to', ...
%                                      'excise marked stretches (Note: Leaves rejection', ...
%                                      'boundary markers in the event table).'), 'Warning', 'Cancel', 'Continue', 'Continue');
%             if strcmpi(res, 'Cancel'), return; end;
%         end;
%     end; 
%     eegplotoptions = { 'events', EEG.event };
%     if ~isempty(EEG.chanlocs) & icacomp
%         eegplotoptions = { eegplotoptions{:}  'eloc_file', EEG.chanlocs };
%     end;
% end;
% 
% effintssize = size(effints);
% fullsize = effintssize(1) * effintssize(2);
% winrej = zeros(fullsize, effintssize(1) + 5);
% for i=1:effintssize(2)
%     for j=1:effintssize(1)
%         effint = effints{j,i};
%         left = effint.offset + effint.left;
%         right = effint.offset + effint.right;
%         channels = zeros(1,effintssize(1));
%         channels(j) = 1;
%         ind = (i-1)*effintssize(2) + j;
%         winrej(ind,1:5) = [left right 1 1 1];
%         winrej(ind,6:end) = channels;
%     end;
% end;
% 
% eegplotoptions = { eegplotoptions{:}  'winrej',winrej };
% 
% if EEG.nbchan > 100
%     disp('pop_eegplot() note: Baseline subtraction disabled to speed up display');
%     eegplotoptions = { eegplotoptions{:} 'submean' 'off' };
% end;
% 
% icadata = (EEG.icaweights*EEG.icasphere)*EEG.data(EEG.icachansind,:);
% eegplot( icadata, 'srate', EEG.srate, 'title', 'Scroll channel activities -- eegplot()', ...
%  			  'limits', [EEG.xmin EEG.xmax]*1000 , 'command', command, eegplotoptions{:}, varargin{:});
% % if icacomp == 1
% % 	eegplot( EEG.data, 'srate', EEG.srate, 'title', 'Scroll channel activities -- eegplot()', ...
% % 			  'limits', [EEG.xmin EEG.xmax]*1000 , 'command', command, eegplotoptions{:}, varargin{:}); 
% % else
% %     tmpdata = eeg_getdatact(EEG, 'component', [1:size(EEG.icaweights,1)]);
% % 	eegplot( tmpdata, 'srate', EEG.srate, 'title', 'Scroll component activities -- eegplot()', ...
% % 			 'limits', [EEG.xmin EEG.xmax]*1000 , 'command', command, eegplotoptions{:}, varargin{:}); 
% % end;
% com = [ com sprintf('pop_eegplot( %s, %d, %d, %d);', inputname(1), icacomp, superpose, reject) ]; 
% return;
