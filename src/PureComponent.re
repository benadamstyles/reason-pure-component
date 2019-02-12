module type StatelessConfig = {
  type retainedProps;
  let name: string;
  let equals: (retainedProps, retainedProps) => bool;
};

module Stateless = (Config: StatelessConfig) => {
  let component = {
    ...ReasonReact.statelessComponentWithRetainedProps(Config.name),
    shouldUpdate:
      (
        {oldSelf, newSelf}:
          ReasonReact.oldNewSelf(
            ReasonReact.stateless,
            Config.retainedProps,
            ReasonReact.actionless,
          ),
      ) =>
      !Config.equals(oldSelf.retainedProps, newSelf.retainedProps),
  };
};
