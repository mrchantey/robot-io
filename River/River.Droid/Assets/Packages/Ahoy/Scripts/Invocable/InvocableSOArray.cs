using UnityEngine;
using System.Collections.Generic;

namespace Ahoy
{
    [CreateAssetMenu(fileName = "InvocableSOArray", menuName = "Ahoy/InvocableSOArray", order = 0)]
    public class InvocableSOArray : InvocableSO
    {
        public List<InvocableSO> invocables;

        public override void Invoke()
        {
            invocables.ForEach(i => i.Invoke());
        }


    }

}