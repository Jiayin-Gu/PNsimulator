import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
import math


def shockley_curve(v, I_s):
	return I_s*(np.exp(v)-1)



def I_V():
	data=np.loadtxt("I_V.out")
	V=data[:, 0]
	I=data[:, 1]


	popt, pcov=curve_fit(shockley_curve, V, I, p0=(0-I[0]))
	I_s=popt[0]
	v=np.linspace(V[0], V[-1], 100)
	i=shockley_curve(v, I_s)

	plt.close()
	fig=plt.figure(figsize=(10, 7), dpi=80)

	ax=fig.add_subplot(1, 1, 1)
	ax.set_xlabel("$V$", fontsize=25)
	ax.set_xlim(V[0], V[-1])
	ax.set_xticks(np.linspace(V[0], V[-1], 10))
	ax.set_xticklabels(["-5", "-4", "-3", "-2", "-1", "0", "1", "2", "3", "4"], fontsize=20)
	ax.set_ylabel(r"$I$ $(\times 10^5)$", fontsize=25)
	ax.set_ylim(-0.8e5, 4.0e5)
	ax.set_yticks(np.linspace(-0.8e5, 4.0e5, 7).tolist())
	ax.set_yticklabels(["-0.8", "0.0", "0.8", "1.6", "2.4", "3.2", "4.0"], fontsize=20)
	plt.scatter(V, I, color="black", marker="*")
	ax.plot(v, i, color="black", linestyle="--", label="Shockley curve")
	ax.grid(linestyle=":", linewidth=0.1, color="gray")
	ax.legend(loc="upper left", fontsize=25)
	ax.text(-4.5, 2.0e5, r"$I=%0.0f\times\left[\exp(V)-1\right]$" % (I_s), fontsize=25)

	plt.tight_layout()
	fig.savefig("I_V.eps")
	plt.close()


I_V()
