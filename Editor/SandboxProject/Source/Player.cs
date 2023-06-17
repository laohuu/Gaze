using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Gaze;

namespace Sandbox
{
    public class Player : Entity
    {
        private TransformComponent m_Transform;
        private Rigidbody2DComponent m_Rigidbody;

        public float Speed;
        public float Time = 0.0f;

        void OnCreate()
        {
            Console.WriteLine($"Player.OnCreate - {ID}");

            m_Transform = GetComponent<TransformComponent>();
            m_Rigidbody = GetComponent<Rigidbody2DComponent>();

            bool hasTransform = HasComponent<TransformComponent>();
            Console.WriteLine($"Player.HasComponent - {hasTransform}");
        }

        void OnUpdate(float ts)
        {
            Time += ts;

            float speed = Speed;
            Vector3 velocity = Vector3.Zero;

            if (Input.IsKeyDown(KeyCode.W))
                velocity.Y = 1.0f;
            else if (Input.IsKeyDown(KeyCode.S))
                velocity.Y = -1.0f;

            if (Input.IsKeyDown(KeyCode.A))
                velocity.X = -1.0f;
            else if (Input.IsKeyDown(KeyCode.D))
                velocity.X = 1.0f;

            velocity *= speed * ts;

            m_Rigidbody.ApplyLinearImpulse(velocity.XY, true);

            //             Vector3 translation = m_Transform.Translation;
            //             translation += velocity * ts;
            //             m_Transform.Translation = translation;
        }

    }
}