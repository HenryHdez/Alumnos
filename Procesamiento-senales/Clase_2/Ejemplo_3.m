x=[0,0,1,1,1,0,0,0];
h=[1,1,1,0,0,0,0,0];
subplot(3,1,1)
stem(x)
axis([0,8,0,4]);
subplot(3,1,2)
stem(h)
axis([0,8,0,4]);
for i=0:8
    subplot(3,1,3)
    h1=circshift(h,i);
    y=sum(h1.*x);
    stem(i,y,'b');
    axis([0,7,0,4]);
    pause(1)
    drawnow
    hold on
end