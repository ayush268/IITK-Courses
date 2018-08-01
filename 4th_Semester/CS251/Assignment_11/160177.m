#!/usr/bin/env octave

warning('off','all');

# Step 1

a = dlmread("train.csv", ",");
a = a(2:length(a), 1:2);

X_train = a(:, 1);
Y_train = a(:, 2);

i = ones(length(X_train),1);
X_train = [i, X_train];


# Step 2

w = rand(2,1);


# Step 3

hold on;
scatter(X_train(:,2), Y_train);
plot(X_train(:,2),(w'*X_train')');

xlabel ("Feature");
ylabel ("Labels");
title ("Graph for Step 3");

print -dpdf "fig1.pdf";
close;


# Step 4

w_direct = (inv(X_train'*X_train))*X_train'*Y_train;

hold on;
scatter(X_train(:,2), Y_train);
plot(X_train(:,2),(w_direct'*X_train')');

xlabel ("Feature");
ylabel ("Labels");
title ("Graph for Step 4");

print -dpdf "fig2.pdf";
close;


# Step 5

N = 2;
eta = 1e-8;
hold on;
scatter(X_train(:,2), Y_train);
plot(X_train(:,2),(w'*X_train')');

xlabel ("Features");
ylabel ("Labels");
title ("Graph for Step 5");

for i = 1:N
  for j = 1:length(X_train)
    x = X_train(j,2);
    y = Y_train(j,1);
    x_new = [1, x];
    w = w - eta*(x_new*w - y)*x_new';
    if(mod(j,200) == 0 && j < 1500)
      plot(X_train(:,2),(w'*X_train')');
    endif
  endfor
endfor

print -dpdf "fig3.pdf";
close;


# Step 6

hold on;
scatter(X_train(:,2), Y_train);
plot(X_train(:,2),(w'*X_train')');

xlabel ("Feature");
ylabel ("Labels");
title ("Graph for Step 6");

print -dpdf "fig4.pdf";
close;


# Step 7

b = dlmread("test.csv", ",");
b = b(2:length(b), 1:2);

X_test = b(:, 1);
Y_test = b(:, 2);

i = ones(length(X_test),1);
X_test = [i, X_test];

Y_pred1 = X_test * w;
Y_pred2 = X_test * w_direct;

rms1 = sum((Y_pred1 - Y_test) .** 2);
rms1 = (rms1 / length(Y_test)) ** 0.5;

rms2 = sum((Y_pred2 - Y_test) .** 2);
rms2 = (rms2 / length(Y_test)) ** 0.5;

disp ("RMS from Training:"), disp(rms1)
disp ("RMS from w_direct:"), disp(rms2)
