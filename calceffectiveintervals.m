function[effints] = calceffectiveintervals(EEG, eventtypes, timeinterval_left, timeinterval_right, constraint_left, constraint_right, superiority_coef, min_int_len)

tic
%effints = calceffectiveintervals_ampl(EEG, eventtypes, timeinterval_left, timeinterval_right, constraint_left, constraint_right, superiority_coef, min_int_len);
%effints = calceffectiveintervals_ersp_max(EEG, eventtypes, timeinterval_left, timeinterval_right, constraint_left, constraint_right, superiority_coef, min_int_len);
effints = calceffectiveintervals_ersp_mean(EEG, eventtypes, timeinterval_left, timeinterval_right, constraint_left, constraint_right, superiority_coef, min_int_len);
%effints = calceffectiveintervals_ersp_union(EEG, eventtypes, timeinterval_left, timeinterval_right, constraint_left, constraint_right, superiority_coef, min_int_len);
toc
