clear; clc;
[A, B, C, D] = tf2ss([1 3],[1 3 2]) %Gp(s)
[Ac, Bc, Cc, Dc] = tf2ss([-768 61920],[1 63 1962]) %Gc(s)
K = Cc;
L = Bc;

[nGc,dGc]=ss2tf(Ac,Bc,Cc,Dc)

Acl = [A B*Cc ; -Bc*C Ac];
Bcl = [zeros(2 ,1) ; Bc];
Ccl = [C , zeros(1,2)];
Dcl = 0;
Nbar = -(inv (Ccl*inv(Acl)*Bcl)) ;
t = 0:0.01:5;
SSsyst = ss(Acl , Bcl , Ccl , Dcl) ;
u = [ones(1 ,max(size(t)))] ;
ycl = lsim(SSsyst ,u' ,t)*Nbar ;

[nGp , dGp]=ss2tf(A ,B ,C ,D) ;
nL=conv(nGc , nGp) ;
dL=conv(dGc , dGp) ;
nT = nL ;
dT = dL + nL ;

y = step(nT ,dT ,t)*Nbar ;
plot(t,y,t,ycl, '--', 'Linewidth' ,2)
title ( ' Identical Responses using Est+Reg and Compensator ' )
xlabel ( ' t ( sec ) ' )
ylabel ( 'y( t ) ' )
