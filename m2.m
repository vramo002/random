clear; clc;
Ts = tf(conv([3 18],[1 12]),conv([1 3],conv([1 6],[1,12])))
p = pole(Ts)
[A,B,C,D] = tf2ss(conv([1 -1],[1 7]),conv([1 1],conv([1 -2],[1,3])));
tf(conv([1 -1],[1 7]),conv([1 1],conv([1 -2],[1,3])))
K = acker(A,B,p);
K = K+.1
Nbar = -inv(C*inv(A-B*K)*B)

Sys1 = ss(A-B*K,B*Nbar,C,D);
t = 0:0.01:5;
[y,t,x]= step(Sys1,t);
plot(t,y,'Linewidth',2);
grid
xlabel('t (sec)')
title(' Step response')

Ts1 = tf(3,conv([1 3],conv([1 6],[1,12])))
p1 = pole(Ts1)
[A1,B1,C1,D1] = tf2ss(conv([1 -1],[1 7]),conv([1 1],conv([1 -2],[1,3])));
K1 = acker(A1,B1,p1);

Sys2 = ss(A1-B1*K1,B1*Nbar,C1,D1);
t1 = 0:0.01:5;
[y1,t1,x1]= step(Sys2,t1);
plot(t,y,"--",t1,y1,'Linewidth',1);
grid
xlabel('t (sec)')
title(' Step response')

[a,b,c,d] = tf2ss(conv([3 18],[1 12]),conv([1 3],conv([1 6],[1,12])))
eig(a)
Gs = tf(conv([1 -1],[1 7]),conv([1 1],conv([1 -2],[1,3])));
