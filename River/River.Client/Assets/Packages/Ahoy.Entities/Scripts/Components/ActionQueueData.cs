using System;
using System.Collections.Generic;
using System.Linq;
using Unity.Entities;
using UnityEngine;


namespace Ahoy.Entities
{

    [Serializable]
    public struct ActionQueueData : ISharedComponentData, IEquatable<ActionQueueData>
    {

        static int idIncr;
        public int id { get; private set; }
        public string name;
        public bool debug;
        public bool debugFull;
        public int maxDispatchesPerUpdate;
        public int frameOffset;
        public int frameModulo;
        public List<ActionQueueItem> items;


        public ActionQueueData(
             string _name = "Action Queue",
            int _maxDispatchesPerUpdate = 2
             )
        {
            id = ++idIncr;
            debug = false;
            debugFull = false;
            name = _name;
            maxDispatchesPerUpdate = _maxDispatchesPerUpdate;
            frameOffset = 0;
            frameModulo = 1;
            items = new List<ActionQueueItem>();
        }

        public void AddAction(Action action)
        {
            AddAction(action, items.Count.ToString());
        }

        public void AddAction(Action action, string id)
        {
            items.Add(new ActionQueueItem(action, id));
        }

        public Promise AddActionAsync(Action action)
        {
            return AddActionAsync(action, items.Count.ToString());
        }

        public Promise AddActionAsync(Action action, string id)
        {
            var prom = new Promise();
            Action promAction = () =>
            {
                action();
                prom.Resolve();
            };
            items.Add(new ActionQueueItem(promAction, id));
            return prom;
        }

        public Promise AddActionsAsync(Action[] actions)
        {
            var proms = new Promise[actions.Length];
            for (int i = 0; i < actions.Length; i++)
            {
                proms[i] = AddActionAsync(actions[i]);
            }
            return Promise.All(proms);
        }

        public Promise<T> AddFunctionAsync<T>(Func<T> func)
        {
            return AddFunctionAsync<T>(func, items.Count.ToString());
        }

        public Promise<T> AddFunctionAsync<T>(Func<T> func, string id)
        {
            var prom = new Promise<T>();
            Action promAction = () =>
            {
                var val = func();
                prom.Resolve(val);
            };
            items.Add(new ActionQueueItem(promAction, id));
            return prom;
        }

        public Promise<T[]> AddFunctionsAsync<T>(Func<T>[] funcs)
        {
            var proms = new Promise<T>[funcs.Length];
            for (int i = 0; i < funcs.Length; i++)
            {
                proms[i] = AddFunctionAsync<T>(funcs[i]);
            }
            return Promise<T>.All(proms);
        }


        public bool Equals(ActionQueueData other)
        {
            return id == other.id;
        }

        public override int GetHashCode()
        {
            return id;
        }

    }
}