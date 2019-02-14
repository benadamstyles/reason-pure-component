# ReasonPureComponent

A PureComponent implementation for ReasonReact. Simplify your `shouldUpdate`!

## Installation

```sh
npm install reason-pure-component
```

**`bsconfig.json`:**

```diff
"bs-dependencies": [
  "reason-react",
+  "reason-pure-component"
]
```

## Usage

Using ReasonPureComponent doesn't result in fewer lines of code, necessarily. The benefit is in the abstraction of how you compare `oldSelf.retainedProps` and `newSelf.retainedProps`. You simply define an equality function – in this case `==` . Thanks to the OCaml type system, if you forget to define any of the required configuration, the program will not compile – whereas if you use `ReasonReact.statelessComponentWithRetainedProps` directly, and forget to define `shouldUpdate`, no one is any the wiser.

```diff
+ module Config = {
    type retainedProps = {
      view: string,
      subview: option(string),
    };
+   let name = "Breadcrumb";
+   let equals = (==);
+ };

- let component =
-    ReasonReact.statelessComponentWithRetainedProps(
-      "Breadcrumb"
-    );

+ module Pure = ReasonPureComponent.Stateless(Config);

let make = (~view, ~subview=?, _children) => {
-  ...component,
+  ...Pure.component,

-  retainedProps: {view, subview},
+  retainedProps: Config.{view, subview},

-  shouldUpdate: (oldAndNewSelf) =>
-    oldAndNewSelf.oldSelf.retainedProps !=
-    oldAndNewSelf.newSelf.retainedProps,

  render: _ =>
    <div>
      <p>{ReasonReact.string(view)}</p>
      <p>
        {ReasonReact.string(
          subview->Belt.Option.getWithDefault("")
        )}
      </p>
    </div>,
};
```
