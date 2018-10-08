function serial_sample(com_num,d_num)

N = 4096;
%使用matlab打开电脑串口读取数据
% clear
% close
a = instrfind;
delete(a);
%str = 'please input com:\n';
%n = ['com',input(str,'s')];
n = ['com',num2str(com_num)];
%新建一个串口对象
obj = serial(n);
%-----------------------------------%
%obj.BytesAvailableFcnMode='byte';
obj.InputBufferSize=N*2;
obj.BytesAvailableFcnCount=48;
obj.BaudRate=115200;
%-----------------------------------%
%str1 = 'please input ad_point:\n';
%d_num = input(str1);
fopen(obj);
%下发采集命令，这里为0x05(存在问题数值，怎么让下位机收到16进制数而不是字符）
% fprintf(obj,'%x',15);
% fwrite(obj,hex2dec(50),'uint8');
fwrite(obj,hex2dec('50'),'uint8');
fwrite(obj,hex2dec('51'),'uint8');
%读取指定点数的AD数据，需要与下位机配合
ad_data = fread(obj,d_num,'uint16');

ad_value = ad_data*3.3/4096;
figure(1)
subplot(2,1,1);
plot(ad_data);
subplot(2,1,2);
plot(ad_value);
% subplot(3,1,3);
% [fft_x,fft_y]=fft_demo(N,ad_data);
% plot(fft_x,fft_y);


%filename为三部分组成，文件内容，当前时间和文件后缀

%生成文件名 adtemp_当前日期.txt
% file_name = ['adtemp_',datestr(now,30),'.txt'];
% file_name = ['adtemp_',datestr(now,30),'.csv'];
% % 打开对应文件名的文件，如不存在 新建
% fileID = fopen(file_name,'w+');
% % 
% %fwrite(fileID,dec2hex(ad_data),'uint16');
% fprintf(fileID,'%d\n',ad_data);

fclose(obj);

end
