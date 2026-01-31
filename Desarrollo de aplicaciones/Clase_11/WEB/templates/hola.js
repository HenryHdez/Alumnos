			const obj = {
				valor: 42,
				metodo: function () {
					setTimeout(() => {
						console.log(this.valor);
					}, 1000);
				}
			};
			
			obj.metodo();