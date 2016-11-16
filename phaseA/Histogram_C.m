function [s] =  Histogram_C(filename,space)

    %# preassign s to some large cell array
    s=cell(10000,1);
    d=[0.05:1/space:1];
    sizS = 10000;
    lineCt = 1;
    fid = fopen(filename);
    tline = fgetl(fid);
    while ischar(tline)
       s{lineCt} = sscanf(tline, '%d');
       
       lineCt = lineCt + 1;
       %# grow s if necessary
       if lineCt > sizS
           s = [s;cell(10000,1)];
           sizS = sizS + 10000;
       end
       tline = fgetl(fid);
    end
    %# remove empty entries in s
    s(lineCt:end) = [];
    s = cell2mat(s);
    s = reshape (s,1,20);
    %[h,b] = hist(s, 0.05:0.05:1);
    %figure; plot(b,h);
    figure;
    bar(d, s, 0.5);
end

