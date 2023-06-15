﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Gaze;

namespace Sandbox
{
	public class Player : Entity
	{
	    public float ID = 1f;

		void OnCreate()
		{
			Console.WriteLine($"Player.OnCreate - {ID}");
		}

		void OnUpdate(float ts)
		{
			Console.WriteLine($"Player.OnUpdate: {ts}");
		}
	}
}